#include "SystemController.h"

#include <cmath>
#include <string>

#include "SafetyManager.h"
#include "StateDetector.h"
#include "ThresholdManager.h"
#include "../hardwareAbstraction/FillLevelSensor.h"
#include "../hardwareAbstraction/HeaterControl.h"
#include "../hardwareAbstraction/TemperatureSensor.h"
#include "../persistenceManager/SettingsStorage.h"
#include "../userInterface/BuzzerController.h"
#include "../userInterface/DisplayController.h"
#include "../userInterface/InputHandler.h"

namespace logic {

SystemController::SystemController(
    hardware::FillLevelSensor &fillSensor,
    hardware::TemperatureSensor &tempSensor, hardware::HeaterControl &heater,
    ui::DisplayController &display, ui::BuzzerController &buzzer,
    ui::InputHandler &input, StateDetector &stateDetector,
    SafetyManager &safetyManager, ThresholdManager &thresholdManager,
    persistence::SettingsStorage &settingsStorage)
    : fillSensor(fillSensor), tempSensor(tempSensor), heater(heater),
      uiController(display), buzzerController(buzzer), inputHandler(input),
      stateDetector(stateDetector), safetyManager(safetyManager),
      thresholdManager(thresholdManager), settingsStorage(settingsStorage) {
    // Einstellungen (z.B. Schwellwerte) aus dem "persistenten" Speicher laden.
    settingsStorage.loadSettings();
    thresholdManager.setWarningThreshold(settingsStorage.getWarningThreshold());
    thresholdManager.setCriticalThreshold(settingsStorage.getCriticalThreshold());

    auto now = std::chrono::steady_clock::now();
    lastSelfTest = now;
    lastChangeTimestamp = now;
}

void SystemController::executeCycle() {
    // 1. Sensoren auslesen
    int fillLevel = fillSensor.readLevel();
    float temperature = tempSensor.readTemperature();

    // Plausibilitätsprüfung beim Einschalten (R4.1)
    if (!startupChecked) {
        startupChecked = performStartupPlausibilityCheck(fillLevel, temperature);
        if (!startupChecked) {
            enterSafetyMode("Startup plausibility failed");
            return;
        }
    }

    // Messwertvalidierung und Sicherheitsmodus, falls keine sinnvollen Werte vorliegen (R2.2)
    if (!fillSensor.isValid()) {
        enterSafetyMode("Sensor error: fill level invalid");
        return;
    }
    if (temperature < -10.0f || temperature > 150.0f) {
        enterSafetyMode("Sensor error: temperature invalid");
        return;
    }

    if (safetyModeActive) {
        // Verlasse Sicherheitsmodus, sobald gültige Werte vorliegen
        safetyModeActive = false;
        uiController.clearDisplay();
        buzzerController.stopTone();
    }

    if (fillLevel <= 5 && lastFillLevel > 5) {
        tempSensor.resetTemperature();
    }

    lastFillLevel = fillLevel;
    
    // 2. Zustandsdetektion aktualisieren
    updateSystemState(fillLevel, temperature);

    // 2.1 Überhitzungserkennung (R2.3)
    if (temperature > 110.0f) {
        safetyManager.emergencyShutdown(heater);
        uiController.showWarning("Critical: overheating");
        buzzerController.playErrorTone();
        return;
    }

    // 3. Safety-Logik / Trockenlaufprüfung
    if (safetyManager.checkDryRun(fillLevel, tempSensor.getDeltaT())) {
        // Trockenlauf erkannt -> Notabschaltung + Fehlerton + Warnung
        safetyManager.emergencyShutdown(heater);
        uiController.showWarning("Dry run detected");
        buzzerController.playErrorTone();
    } else if (fillLevel < thresholdManager.getCriticalThreshold()) {
        // Kritischer Füllstand -> Heizung aus, Warnung + Warnton
        heater.switchOff();
        uiController.showWarning("Critical fill level");
        buzzerController.playWarningTone();
    } else if (fillLevel < thresholdManager.getWarningThreshold()) {
        // Warnschwelle unterschritten -> Heizung an, Warnung + Warnton
        heater.switchOn();
        uiController.showWarning("Low fill level");
        buzzerController.playWarningTone();
    } else {
        // Normalbetrieb -> Heizung an, Anzeige ohne Warnung, kein Ton
        heater.switchOn();
        uiController.clearDisplay();
        buzzerController.stopTone();
    }

    // 4. Anzeige aktualisieren (Füllstand, Temperatur, aktueller Zustand)
    uiController.updateDisplay(fillLevel, static_cast<int>(temperature),
                               stateDetector.getState());

    // 5. Benutzereingabe (OK-Taste etc.) auswerten
    bool buttonState = inputHandler.readInput();
    bool buttonPressed = buttonState && !lastButtonState;
    lastButtonState = buttonState;

    if (buttonPressed) {
        if (!uiController.getWarningMessage().empty()) {
            acknowledgeWarning();
        } else {
            adjustWarningThreshold();
        }
    }

    // 6. Zyklischer Selbsttest (R4.3)
    runSelfTest(fillLevel, temperature);
}

void SystemController::updateSystemState(int fillLevel, float temperature) {
    //int fillLevel = fillSensor.readLevel();
    //float temperature = tempSensor.readTemperature();
    //stateDetector.detectState(fillLevel, temperature);
    // Zustandsdetektion delegiert an StateDetector
    stateDetector.detectState(fillLevel, temperature);
}

void SystemController::handleError(int errorCode) {
    // Generische Fehlerbehandlung: Heizung aus, Fehlerton, Fehlertext anzeigen
    heater.switchOff();
    buzzerController.playErrorTone();
    uiController.showWarning("Error code: " + std::to_string(errorCode));
}

bool SystemController::performStartupPlausibilityCheck(int fillLevel,
                                                      float temperature) {
    bool fillOk = fillLevel >= 0 && fillLevel <= 100;
    bool tempOk = temperature >= 0.0f && temperature <= 50.0f;
    return fillOk && tempOk;
}

void SystemController::enterSafetyMode(const std::string &reason) {
    safetyModeActive = true;
    heater.switchOff();
    uiController.showWarning(reason);
    buzzerController.playErrorTone();
}

void SystemController::runSelfTest(int fillLevel, float temperature) {
    auto now = std::chrono::steady_clock::now();

    if (fillLevel != lastObservedFill ||
        std::fabs(temperature - lastObservedTemperature) > 0.1f) {
        lastObservedFill = fillLevel;
        lastObservedTemperature = temperature;
        lastChangeTimestamp = now;
    }

    if (now - lastSelfTest >= std::chrono::seconds(30)) {
        if (now - lastChangeTimestamp >= std::chrono::seconds(10)) {
            uiController.showWarning("Self-test: values unchanged");
            buzzerController.playWarningTone();
        }
        lastSelfTest = now;
    }
}

void SystemController::acknowledgeWarning() {
    uiController.clearWarning();
    buzzerController.stopTone();
    if (safetyManager.isDryRunDetected()) {
        heater.switchOff();
    }
}

void SystemController::adjustWarningThreshold() {
    int current = thresholdManager.getWarningThreshold();
    int next = current + 5;
    if (next > 50) {
        next = 10;
    }

    thresholdManager.setWarningThreshold(next);
    settingsStorage.setWarningThreshold(next);
    settingsStorage.saveSettings();
    uiController.showWarning("Warning threshold: " + std::to_string(next) + "%");
}

} // namespace logic

