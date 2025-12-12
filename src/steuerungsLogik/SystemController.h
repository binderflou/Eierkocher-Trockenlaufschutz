#pragma once

#include <chrono>
#include <memory>
#include <string>

namespace hardware {
class FillLevelSensor;
class TemperatureSensor;
class HeaterControl;
}

namespace ui {
class DisplayController;
class BuzzerController;
class InputHandler;
}

namespace persistence {
class SettingsStorage;
}

namespace logic {

class StateDetector;
class SafetyManager;
class ThresholdManager;

/**
 * @brief Zentrale Steuerungsklasse des Systems.
 *
 * Der SystemController koordiniert das Zusammenspiel von
 * Sensoren, Safety-Logik, Zustandsdetektion, Anzeige und Benutzerinteraktionen.
 */
class SystemController {
public:
    SystemController(hardware::FillLevelSensor &fillSensor,
                     hardware::TemperatureSensor &tempSensor,
                     hardware::HeaterControl &heater,
                     ui::DisplayController &display,
                     ui::BuzzerController &buzzer,
                     ui::InputHandler &input,
                     StateDetector &stateDetector,
                     SafetyManager &safetyManager,
                     ThresholdManager &thresholdManager,
                     persistence::SettingsStorage &settingsStorage);

    /**
    * @brief Führt einen Steuerungszyklus aus.
    *
    * - Sensorwerte lesen
    * - Zustände aktualisieren
    * - Safety-Funktionen prüfen (Trockenlauf etc.)
    * - Heizung / Buzzer / Display steuern
    */
    void executeCycle();
    
    /**
    * @brief Aktualisiert den logischen Systemzustand anhand aktueller Werte
    *
    * @param fillLevel   Aktueller Füllstand
    * @param temperature Aktuelle Temperatur
    */
    void updateSystemState(int fillLevel, float temperature);
    
    /**
     * @brief Fehlerbehandlung
     */
    void handleError(int errorCode);

    // Von main() aufgerufen (Konsole)
    void onFillPressed(); // Taste 'F'
    
    void onAckPressed();  // Taste 'A'

private:
    bool performStartupPlausibilityCheck(int fillLevel, float temperature);
    void enterSafetyMode(const std::string &reason);
    void runSelfTest(int fillLevel, float temperature);
    void acknowledgeWarning();
    void adjustWarningThreshold();

    hardware::FillLevelSensor &fillSensor;
    hardware::TemperatureSensor &tempSensor;
    hardware::HeaterControl &heater;
    ui::DisplayController &uiController;
    ui::BuzzerController &buzzerController;
    ui::InputHandler &inputHandler;
    StateDetector &stateDetector;
    SafetyManager &safetyManager;
    ThresholdManager &thresholdManager;
    persistence::SettingsStorage &settingsStorage;
    bool startupChecked = false;
    bool safetyModeActive = false;
    int lastFillLevel = 100;
    std::chrono::steady_clock::time_point lastSelfTest;
    std::chrono::steady_clock::time_point lastChangeTimestamp;
    int lastObservedFill = -1;
    float lastObservedTemperature = -999.0f;
    bool lastButtonState = false;
    bool waitingForFill = false;
    bool waitingForAck = false;
    int lastUiFill_ = 0;
    float lastUiTemp_ = 20.0f;
};

} // namespace logic

