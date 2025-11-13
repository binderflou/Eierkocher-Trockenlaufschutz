#pragma once

#include <memory>

namespace persistence {

class CalibrationData;

class SettingsStorage {
public:
    SettingsStorage();

    void loadSettings();
    void saveSettings();

    int getWarningThreshold() const;
    int getCriticalThreshold() const;

    void setWarningThreshold(int value);
    void setCriticalThreshold(int value);

    CalibrationData &getCalibrationData();
    const CalibrationData &getCalibrationData() const;

private:
    int warningThreshold;
    int criticalThreshold;
    std::unique_ptr<CalibrationData> calibration;
};

} // namespace persistence

