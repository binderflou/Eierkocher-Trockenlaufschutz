#include "TimerService.h"

#include <chrono>

namespace hardware {

TimerService::TimerService()
    : lastUpdate(std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::steady_clock::now().time_since_epoch())
          .count()) {}

bool TimerService::elapsed(std::int64_t ms) {
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now().time_since_epoch())
                   .count();
    if (now - lastUpdate >= ms) {
        lastUpdate = now;
        return true;
    }
    return false;
}

} // namespace hardware

