#pragma once

#include <string>

namespace ui {

class DisplayController {
public:
    DisplayController();

    void updateDisplay(int fillLevel, int temperature, const std::string &status);
    void showWarning(const std::string &message);
    void clearDisplay();

    int getFillLevelDisplay() const;
    int getTemperatureDisplay() const;
    std::string getWarningMessage() const;

private:
    int fillLevelDisplay;
    int temperatureDisplay;
    std::string warningMessage;
};

} // namespace ui

