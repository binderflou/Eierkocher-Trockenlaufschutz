#include "HeaterControl.h"

namespace hardware {

HeaterControl::HeaterControl(int relayPin)
    : relayPin(relayPin), isOn(false) {}

//Heizung als EIN markieren
void HeaterControl::switchOn() { isOn = true; }

//Heizung als AUS markieren
void HeaterControl::switchOff() { isOn = false; }

//akt. Simulationsstatus Heizung zurückgeben
bool HeaterControl::getStatus() const { return isOn; }

} // namespace hardware

