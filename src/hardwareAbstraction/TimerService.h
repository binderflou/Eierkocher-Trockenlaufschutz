#pragma once

#include <cstdint>

namespace hardware {

class TimerService {
public:
    TimerService();

    bool elapsed(std::int64_t ms);

private:
    std::int64_t lastUpdate;
};

} // namespace hardware

