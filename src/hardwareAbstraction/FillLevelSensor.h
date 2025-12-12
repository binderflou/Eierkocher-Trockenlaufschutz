#pragma once

#include <memory>

namespace hardware {

class TimerService;
    
    /**
    * @brief Simulierter Füllstandssensor.
    *
    * In der echten Hardware würde hier ein analoger Eingang ausgelesen.
    * In der Simulation wird ein Füllstandswert intern hoch/runter gezählt.
    */
class FillLevelSensor {
public:
    /**
     * @brief Konstruktor
     * @param analogPin     Pin-Nummer des (simulierten) Analog-Eingangs.
     * @param timerService  Gemeinsamer Timer-Service, um das Aktualisierungs-
     *                      intervall zu steuern.
     */
    explicit FillLevelSensor(int analogPin,
                             std::shared_ptr<TimerService> timerService);

    /**
     * @brief Liefert den aktuellen Füllstandswert (0–100 %).
     *
     * Die Methode aktualisiert mit einem gewissen Zeitintervall den
     * internen Simulationswert und gibt ihn anschließend zurück.
     */
    int readLevel();

    //Gibt an, ob bereits ein gültiger Wert gelesen wurde.
    bool isValid() const;

    // Auto-Refill (bei 0 -> 100) ein/aus
    void setAutoRefillEnabled(bool enabled);

    // Manuelles Füllen (z.B. Taste 'F')
    void refillToFull();

private:
    int analogPin;  //simuliert Analog Pin
    int fillLevelPercent;   //aktueller Füllstand (%)
    bool valid; //true, sobald mind. ein gültiger Wert vorliegt
    std::shared_ptr<TimerService> timerService; //Timer für die zeitgesteurte Simulation
    bool autoRefillEnabled;
};

} // namespace hardware

