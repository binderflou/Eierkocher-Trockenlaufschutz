#pragma once

#include <memory>

namespace hardware {

class TimerService;

class TemperatureSensor {
public:
    explicit TemperatureSensor(int tempPin,
                               std::shared_ptr<TimerService> timerService);

    float readTemperature();
    void resetTemperature();
    float getDeltaT() const;

private:
    int tempPin;
    float temperature;
    float lastTemperature;
    std::shared_ptr<TimerService> timerService;
};

} // namespace hardware

