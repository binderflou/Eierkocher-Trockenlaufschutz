#include "SettingsStorage.h"

#include <memory>

#include "CalibrationData.h"

namespace persistence {

SettingsStorage::SettingsStorage()
    : warningThreshold(20), criticalThreshold(5),
      calibration(std::make_unique<CalibrationData>()) {}

void SettingsStorage::loadSettings() {
    warningThreshold = 25;
    criticalThreshold = 10;
}

void SettingsStorage::saveSettings() {
    // Placeholder for persisting settings.
}

int SettingsStorage::getWarningThreshold() const { return warningThreshold; }

int SettingsStorage::getCriticalThreshold() const { return criticalThreshold; }

void SettingsStorage::setWarningThreshold(int value) { warningThreshold = value; }

void SettingsStorage::setCriticalThreshold(int value) { criticalThreshold = value; }

CalibrationData &SettingsStorage::getCalibrationData() { return *calibration; }

const CalibrationData &SettingsStorage::getCalibrationData() const {
    return *calibration;
}

} // namespace persistence

