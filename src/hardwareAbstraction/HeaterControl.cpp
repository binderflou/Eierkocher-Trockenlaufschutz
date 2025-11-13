#include "HeaterControl.h"

namespace hardware {

HeaterControl::HeaterControl(int relayPin)
    : relayPin(relayPin), isOn(false) {}

void HeaterControl::switchOn() { isOn = true; }

void HeaterControl::switchOff() { isOn = false; }

bool HeaterControl::getStatus() const { return isOn; }

} // namespace hardware

