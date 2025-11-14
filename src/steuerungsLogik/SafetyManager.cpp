#include "SafetyManager.h"

#include "../hardwareAbstraction/HeaterControl.h"

namespace logic {

SafetyManager::SafetyManager() : dryRunDetected(false) {}

bool SafetyManager::checkDryRun(int fillLevel, float tempRise) {
    //Füllstand<5% und Temp. Anstieg > 5°C pro Messintervall
    dryRunDetected = fillLevel < 5 && tempRise > 5.0f;
    return dryRunDetected;
}

void SafetyManager::emergencyShutdown(hardware::HeaterControl &heater) {
    // Nur wenn dryRunDetected gesetzt ist, wird die Heizung abgeschaltet.
    if (dryRunDetected) {
        heater.switchOff();
    }
}

bool SafetyManager::isDryRunDetected() const { return dryRunDetected; }

} // namespace logic

