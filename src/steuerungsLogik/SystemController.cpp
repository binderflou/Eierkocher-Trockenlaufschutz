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
    settingsStorage.loadSettings();
    thresholdManager.setWarningThreshold(settingsStorage.getWarningThreshold());
    thresholdManager.setCriticalThreshold(settingsStorage.getCriticalThreshold());
}

void SystemController::executeCycle() {
    int fillLevel = fillSensor.readLevel();
    float temperature = tempSensor.readTemperature();
   
    if (fillLevel <= 5 && lastFillLevel > 5) {
        tempSensor.resetTemperature();
    }

    lastFillLevel = fillLevel;

    updateSystemState(fillLevel, temperature);

    if (safetyManager.checkDryRun(fillLevel, tempSensor.getDeltaT())) {
        safetyManager.emergencyShutdown(heater);
        uiController.showWarning("Dry run detected");
        buzzerController.playErrorTone();
    } else if (fillLevel < thresholdManager.getCriticalThreshold()) {
        heater.switchOff();
        uiController.showWarning("Critical fill level");
        buzzerController.playWarningTone();
    } else if (fillLevel < thresholdManager.getWarningThreshold()) {
        heater.switchOn();
        uiController.showWarning("Low fill level");
        buzzerController.playWarningTone();
    } else {
        heater.switchOn();
        uiController.clearDisplay();
        buzzerController.stopTone();
    }

    uiController.updateDisplay(fillLevel, static_cast<int>(temperature),
                               stateDetector.getState());

    if (inputHandler.readInput()) {
        buzzerController.stopTone();
    }
}

void SystemController::updateSystemState(int fillLevel, float temperature) {
    //int fillLevel = fillSensor.readLevel();
    //float temperature = tempSensor.readTemperature();
    //stateDetector.detectState(fillLevel, temperature);
    stateDetector.detectState(fillLevel, temperature);
}

void SystemController::handleError(int errorCode) {
    heater.switchOff();
    buzzerController.playErrorTone();
    uiController.showWarning("Error code: " + std::to_string(errorCode));
}

} // namespace logic

