#pragma once

#include <memory>

namespace hardware {

class TimerService;

/**
 * @brief Simulierter Temperatursensor.
 *
 * Die Temperatur steigt in der Simulation schrittweise an, um
 * den Aufheizvorgang des Wassers zu imitieren.
 */
class TemperatureSensor {
public:
    /**
    * @brief Konstruktor
    * @param tempPin       Pin, an dem der Sensor im echten System hängen würde.
    * @param timerService  Timer zur Steuerung der Simulationsschritte.
    */
    explicit TemperatureSensor(int tempPin,
                               std::shared_ptr<TimerService> timerService);

    /**
     * @brief Liest die (simulierte) Temperatur.
     *
     * Bei jedem ausreichend großen Zeitintervall wird die Temperatur
     * erhöht, bis ein Maximalwert (z.B. 100 °C) erreicht ist.
     */
    float readTemperature();
    
    //Temp zurücksetzen
    void resetTemperature();
    
    /**
     * @brief Liefert die Temperaturänderung seit der letzten Aktualisierung.
     *
     * @return temperature - lastTemperature
     */
    float getDeltaT() const;

private:
    int tempPin;    //Simulierter Pin des Temp Sensors
    float temperature;  //akt. Temperaturwerte
    float lastTemperature;  //Temp Wert der letzten Aktualiserung
    std::shared_ptr<TimerService> timerService; //Timer für Sim
};

} // namespace hardware

