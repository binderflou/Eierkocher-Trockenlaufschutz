#pragma once

#include <memory>

namespace hardware {

class TimerService;

class FillLevelSensor {
public:
    explicit FillLevelSensor(int analogPin,
                             std::shared_ptr<TimerService> timerService);

    int readLevel();
    bool isValid() const;

private:
    int analogPin;
    int fillLevelPercent;
    bool valid;
    std::shared_ptr<TimerService> timerService;
};

} // namespace hardware

