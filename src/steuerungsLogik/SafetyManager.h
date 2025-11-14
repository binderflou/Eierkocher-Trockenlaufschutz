#pragma once

namespace hardware {
class HeaterControl;
}

namespace logic {

/**
* @brief Verwaltet sicherheitsrelevante Funktionen wie die Trockenlaufüberwachung.
*
* Der SafetyManager prüft Bedingungen, die auf einen Trockenlauf schließen lassen,
* und kann im Fehlerfall eine Notabschaltung der Heizung auslösen.
*/
class SafetyManager {
public:
    SafetyManager();
    
    /**
    * @brief Prüft, ob ein Trockenlauf vorliegt.
    *
    * @param fillLevel Aktueller Füllstand in %.
    * @param tempRise  Temperaturanstieg (Delta T) seit letzter Messung.
    * @return true, wenn Trockenlauf erkannt wurde.
    */
    bool checkDryRun(int fillLevel, float tempRise);
    
    /**
     * @brief Notabschaltung der Heizung.
     *
     * Schaltet die Heizung aus, falls zuvor ein Trockenlauf erkannt wurde.
     */
    void emergencyShutdown(hardware::HeaterControl &heater);
    
    /**
     * @brief Liefert zurück, ob aktuell ein Trockenlauf erkannt ist.
     */
    bool isDryRunDetected() const;

private:
    bool dryRunDetected;    //Trockenlauf erkannt JA/NEIN
};

} // namespace logic

