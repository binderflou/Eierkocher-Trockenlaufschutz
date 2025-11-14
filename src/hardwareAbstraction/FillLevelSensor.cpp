#include "FillLevelSensor.h"

#include <utility>

#include "TimerService.h"

namespace hardware {

FillLevelSensor::FillLevelSensor(int analogPin,
                                 std::shared_ptr<TimerService> timerService)
    : analogPin(analogPin), fillLevelPercent(0), valid(false),
      timerService(std::move(timerService)) {}

int FillLevelSensor::readLevel() {
    // Aktualisiere den Simulationswert nur, wenn seit der letzten Aktualisierung
    // mindestens 50 ms vergangen sind.
    if (timerService && timerService->elapsed(50)) {
        if (fillLevelPercent == 0) {
            // Tank wieder füllen, wenn leer, Reset
            fillLevelPercent = 100;
        }
        else {
            // Ansonsten sinkt der Füllstand in Schritten von 5 %.
            // Dies simuliert das Verdampfen/Verbrauchen des Wassers.
            fillLevelPercent -= 5; // oder -2, -5, je nach gewünschter Geschwindigkeit
            
            if (fillLevelPercent < 0) {
                fillLevelPercent = 0; // Sicherheitshalber auf 0 clampen.
            }
        }
        //ab hier Füllstand gültig
        valid = true;
    }
    return fillLevelPercent;
}

bool FillLevelSensor::isValid() const { return valid; }

} // namespace hardware

