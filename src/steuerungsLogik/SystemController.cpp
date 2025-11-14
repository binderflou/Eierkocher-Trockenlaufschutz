#include "SystemController.h"

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
}

void SystemController::executeCycle() {
    // 1. Sensoren auslesen
    int fillLevel = fillSensor.readLevel();
    float temperature = tempSensor.readTemperature();
   
    if (fillLevel <= 5 && lastFillLevel > 5) {
        tempSensor.resetTemperature();
    }

    lastFillLevel = fillLevel;
    
    // 2. Zustandsdetektion aktualisieren
    updateSystemState(fillLevel, temperature);
    
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
    if (inputHandler.readInput()) {
        // In dieser Simulation: Jeder Tastendruck stoppt den Ton
        buzzerController.stopTone();
    }
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

} // namespace logic

