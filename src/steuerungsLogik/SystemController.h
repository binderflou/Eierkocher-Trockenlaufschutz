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

    void executeCycle();
    void updateSystemState();
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
};

} // namespace logic

