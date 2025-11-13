#include "ThresholdManager.h"

namespace logic {

ThresholdManager::ThresholdManager() : warningThreshold(20), criticalThreshold(5) {}

void ThresholdManager::setWarningThreshold(int value) { warningThreshold = value; }

int ThresholdManager::getWarningThreshold() const { return warningThreshold; }

void ThresholdManager::setCriticalThreshold(int value) { criticalThreshold = value; }

int ThresholdManager::getCriticalThreshold() const { return criticalThreshold; }

} // namespace logic

