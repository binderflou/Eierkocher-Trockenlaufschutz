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
        fillLevelPercent = (fillLevelPercent + 5) % 105;
        valid = true;
    }
    return fillLevelPercent;
}

bool FillLevelSensor::isValid() const { return valid; }

} // namespace hardware

