#include "DisplayController.h"

namespace ui {

DisplayController::DisplayController()
    : fillLevelDisplay(0), temperatureDisplay(0), statusText("Idle") {}

void DisplayController::updateDisplay(int fillLevel, int temperature,
                                      const std::string &status) {
    // Die eigentlichen Anzeigewerte werden übernommen.
    fillLevelDisplay = fillLevel;
    temperatureDisplay = temperature;
    statusText = status;
}

void DisplayController::showWarning(const std::string &message) {
    //überschreibt aktuelle Warnung
    warningMessage = message;
    statusText = "Warning";
}

void DisplayController::clearWarning() {
    warningMessage.clear();
}

void DisplayController::clearDisplay() {
    fillLevelDisplay = 0;
    temperatureDisplay = 0;
    warningMessage.clear();
    statusText.clear();
}

int DisplayController::getFillLevelDisplay() const { return fillLevelDisplay; }

int DisplayController::getTemperatureDisplay() const { return temperatureDisplay; }

std::string DisplayController::getWarningMessage() const { return warningMessage; }

std::string DisplayController::getStatusText() const { return statusText; }

} // namespace ui

