#include "StateDetector.h"

namespace logic {

StateDetector::StateDetector() : currentState("Idle") {}

std::string StateDetector::detectState(int fillLevel, float temperature) {
    //Bei Füllstand <= 10 % -> "LowFill"
    //Bei Temperatur >= 100 °C -> "Boiling"
    //Sonst -> "Heating"
    if (fillLevel <= 10) {
        currentState = "LowFill";
    } else if (temperature >= 100.0f) {
        currentState = "Boiling";
    } else {
        currentState = "Heating";
    }
    return currentState;
}

std::string StateDetector::getState() const { return currentState; }

} // namespace logic

