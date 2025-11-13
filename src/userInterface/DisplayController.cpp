#include "DisplayController.h"

namespace ui {

DisplayController::DisplayController()
    : fillLevelDisplay(0), temperatureDisplay(0) {}

void DisplayController::updateDisplay(int fillLevel, int temperature,
                                      const std::string &status) {
    fillLevelDisplay = fillLevel;
    temperatureDisplay = temperature;
    warningMessage = status;
}

void DisplayController::showWarning(const std::string &message) {
    warningMessage = message;
}

void DisplayController::clearDisplay() {
    fillLevelDisplay = 0;
    temperatureDisplay = 0;
    warningMessage.clear();
}

int DisplayController::getFillLevelDisplay() const { return fillLevelDisplay; }

int DisplayController::getTemperatureDisplay() const { return temperatureDisplay; }

std::string DisplayController::getWarningMessage() const { return warningMessage; }

} // namespace ui

