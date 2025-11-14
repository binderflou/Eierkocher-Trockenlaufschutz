#pragma once

#include <cstdint>

namespace hardware {

/**
* @brief Einfacher Timer-Service zur Messung verstrichener Zeit.
*
* Die Klasse kapselt eine Zeitbasis (Millisekunden seit Start)
* und bietet eine Methode elapsed(ms), die true liefert,
* wenn seit dem letzten erfolgreichen Aufruf mindestens ms Millisekunden
* vergangen sind.
*/
class TimerService {
public:
    TimerService();

    /**
     * @brief Prüft, ob seit der letzten Flanke mindestens ms ms vergangen sind.
     *
     * @param ms Mindestzeit in Millisekunden.
     * @return true, wenn die Zeitspanne seit dem letzten Update >= ms ist.
     *
     * Bei true wird der interne Zeitstempel lastUpdate auf "jetzt" gesetzt.
     */
    bool elapsed(std::int64_t ms);

private:
    std::int64_t lastUpdate;    //Zeitstempel der letzen erfolgreichen elapsed()
};

} // namespace hardware

