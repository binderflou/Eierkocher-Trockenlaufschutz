#pragma once

namespace logic {

/**
* @brief Verwaltet die Schwellwerte für Warn- und kritischen Füllstand.
*/
class ThresholdManager {
public:
    ThresholdManager();
    
    //erste Warnung
    //Setzt Warnschwelle zw. 10% und 50%
    void setWarningThreshold(int value);
    //gibt Warnschwelle zurück
    int getWarningThreshold() const;
    
    //zweite Warnung
    //setzt krit. Füllstandsschwelle
    void setCriticalThreshold(int value);
    //bit die kritische Schwelle zurück
    int getCriticalThreshold() const;

private:
    int warningThreshold;   //Schwelle für Warnzustand 'Low Fill'
    int criticalThreshold;  //Schwelle für krit. Zustand (Heizung AUS)
};

} // namespace logic

