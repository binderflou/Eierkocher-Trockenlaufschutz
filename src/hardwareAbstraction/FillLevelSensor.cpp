#include "FillLevelSensor.h"

#include <utility>

#include "TimerService.h"

namespace hardware {

FillLevelSensor::FillLevelSensor(int analogPin,
                                 std::shared_ptr<TimerService> timerService)
    : analogPin(analogPin), fillLevelPercent(0), valid(false),
      timerService(std::move(timerService)) {}

int FillLevelSensor::readLevel() {
    if (timerService && timerService->elapsed(50)) {
        if (fillLevelPercent == 0) {
            // Tank wieder füllen, wenn leer, Reset
            fillLevelPercent = 100;
        }
        else {
            fillLevelPercent -= 5; // oder -2, -5, je nach gewünschter Geschwindigkeit
        }

        valid = true;
    }
    return fillLevelPercent;
}

bool FillLevelSensor::isValid() const { return valid; }

} // namespace hardware

