#pragma once

#include <memory>

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

private:
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
    int lastFillLevel = 100;
};

} // namespace logic

