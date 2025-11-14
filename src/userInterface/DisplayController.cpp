#include "DisplayController.h"

namespace ui {

DisplayController::DisplayController()
    : fillLevelDisplay(0), temperatureDisplay(0) {}

void DisplayController::updateDisplay(int fillLevel, int temperature,
                                      const std::string &status) {
    // Die eigentlichen Anzeigewerte werden übernommen.
    fillLevelDisplay = fillLevel;
    temperatureDisplay = temperature;
    //Status könnte hier noch optional gespeichert werden
}

void DisplayController::showWarning(const std::string &message) {
    //überschreibt aktuelle Warnung
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

