#include "TimerService.h"

#include <chrono>

namespace hardware {

TimerService::TimerService()
// Initialisiere lastUpdate mit der aktuellen Zeit in Millisekunden
    : lastUpdate(std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::steady_clock::now().time_since_epoch())
          .count()) {}

bool TimerService::elapsed(std::int64_t ms) {
    // Hole aktuelle Zeit in Millisekunden
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now().time_since_epoch())
                   .count();
    // Prüfe, ob seit dem letzten Update mindestens ms Millisekunden vergangen sind
    if (now - lastUpdate >= ms) {
        // Wenn ja, schiebe lastUpdate auf "jetzt" und melde true
        lastUpdate = now;
        return true;
    }
    // Ansonsten ist das Intervall noch nicht abgelaufen
    return false;
}

} // namespace hardware

