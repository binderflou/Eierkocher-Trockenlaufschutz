#include "SafetyManager.h"

#include "../hardwareAbstraction/HeaterControl.h"

namespace logic {

SafetyManager::SafetyManager() : dryRunDetected(false) {}

bool SafetyManager::checkDryRun(int fillLevel, float tempRise) {
    // Wenn Trockenlauf bereits erkannt wurde, bleibt er aktiv
    // bis resetDryRun() aufgerufen wird (z.B. nach 'A').
    if (dryRunDetected) {
        return true;
    }

    // Erst-Erkennung: Füllstand < 5% UND Temperaturanstieg > 5°C pro Messintervall
    if (fillLevel < 5 && tempRise > 5.0f) {
        dryRunDetected = true;
    }

    return dryRunDetected;
}

void SafetyManager::emergencyShutdown(hardware::HeaterControl &heater) {
    // Nur wenn dryRunDetected gesetzt ist, wird die Heizung abgeschaltet.
    if (dryRunDetected) {
        heater.switchOff();
    }
}

bool SafetyManager::isDryRunDetected() const { return dryRunDetected; }

void SafetyManager::resetDryRun() {
    dryRunDetected = false;
}

} // namespace logic