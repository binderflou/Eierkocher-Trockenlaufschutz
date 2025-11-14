#pragma once

#include <string>

namespace ui {

    /**
     * @brief Simulierte Anzeigeeinheit (Display) des Eierkochers.
     *
     * Die Klasse speichert die anzuzeigenden Werte intern,
     * damit sie z.B. aus der main-Schleife abgefragt und in der Konsole
     * ausgegeben werden können.
     */

class DisplayController {
public:
    DisplayController();

    /**
     * @brief Aktualisiert die Hauptanzeige.
     *
     * @param fillLevel    Füllstand in Prozent (0–100).
     * @param temperature  Temperatur in °C.
     * @param status       Textueller Status (z.B. "Heating", "LowFill"...).
     *
     * In der Simulation wird der Status-String aktuell nicht separat
     * gespeichert, sondern nur für die externe Ausgabe genutzt, wenn
     * irgendwo gemerkt. Die eigentliche Anzeige speichert nur
     * Füllstand, Temperatur und optional eine Warnmeldung.
     */
    void updateDisplay(int fillLevel, int temperature, const std::string &status);
    /**
    *@brief Zeigt eine Warnmeldung auf dem Display an.
    *
    * Typische Meldungen : "Low fill level", "Critical fill level", "Füllen!".
    */
    void showWarning(const std::string &message);
    
    //setzt Displaywerte zurück (0, Warnmeldung löschen)
    void clearDisplay();
    //lieferen die zuletzt angezeigten Werte
    int getFillLevelDisplay() const;
    int getTemperatureDisplay() const;
    //liefert aktuell gesetzte Warnmeldung
    std::string getWarningMessage() const;

private:
    int fillLevelDisplay;
    int temperatureDisplay;
    std::string warningMessage;
};

} // namespace ui

