#pragma once

#include <string>

namespace logic {

/**
* @brief Ermittelt den aktuellen logischen Systemzustand.
*
* Aus Füllstand und Temperatur wird ein einfacher Zustandsstring
* wie "LowFill", "Boiling" oder "Heating" abgeleitet.
*/
class StateDetector {
public:
    StateDetector();

    /**
     * @brief Ermittelt den Zustand anhand von Füllstand und Temperatur.
     *
     * @param fillLevel   Füllstand in %.
     * @param temperature Temperatur in °C.
     * @return Der berechnete Zustandsstring.
     */
    std::string detectState(int fillLevel, float temperature);
    /**
     * @brief Liefert den zuletzt ermittelten Zustand.
     */
    std::string getState() const;

private:
    std::string currentState;   //intern gehaltener Zustand
};

} // namespace logic

