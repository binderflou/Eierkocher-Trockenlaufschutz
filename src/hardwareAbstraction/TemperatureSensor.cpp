#include "TemperatureSensor.h"

#include <utility>

#include "TimerService.h"

namespace hardware {

TemperatureSensor::TemperatureSensor(
    int tempPin, std::shared_ptr<TimerService> timerService)
    : tempPin(tempPin), temperature(20.0f), lastTemperature(20.0f),
      timerService(std::move(timerService)) {}

float TemperatureSensor::readTemperature() {
    if (timerService && timerService->elapsed(50)) {
        lastTemperature = temperature;
        temperature += 0.5f;
    }
    return temperature;
}

float TemperatureSensor::getDeltaT() const { return temperature - lastTemperature; }

} // namespace hardware

//test