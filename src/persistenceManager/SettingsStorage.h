#pragma once

#include <memory>

namespace persistence {

class CalibrationData;

/**
 * @brief Verwaltet die persistenten Einstellungen des Systems.
 *
 * Dazu gehören z.B. Warn- und Kritisch-Schwellen für den Füllstand
 * sowie Kalibrierdaten.
 */
class SettingsStorage {
public:
    SettingsStorage();
    
    //lädt Einstellungen (hier simulierte feste Werte)
    void loadSettings();
    //Speichert Einstellungen(akt. Platzhalter)
    void saveSettings();
    //get krit. Warnschwelle in %, ab wann 'Low Fill'
    int getWarningThreshold() const;
    //get krit Schwelle in %, ab wann Heizung AUS
    int getCriticalThreshold() const;
    //setzt kritische Warnschwellen
    void setWarningThreshold(int value);
    void setCriticalThreshold(int value);
    //seitzt Kalibrierdaten auf nicht const
    CalibrationData &getCalibrationData();
    //Zugriff auf Kalibrierdaten (const)
    const CalibrationData &getCalibrationData() const;

private:
    int warningThreshold;   //Füllstandswarnschwelle
    int criticalThreshold;  //Füllstandswarnschwelle für krit. Zustand
    std::unique_ptr<CalibrationData> calibration;   //Kalibrierdatenobj.
};

} // namespace persistence

