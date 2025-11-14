#pragma once

namespace ui {

 /**
 * @brief Simulierter Buzzer / Summer des Eierkochers.
 *
 * Diese Klasse abstrahiert die Ansteuerung eines Buzzers.
 * In der Simulation wird nur ein boolescher Zustand gehalten,
 * ob gerade "ein Ton gespielt" wird oder nicht.
 */

class BuzzerController {
public:

    /**
     * @brief Konstruktor
     * @param buzzerPin Pin-Nummer, an dem der Buzzer im echten System hängen würde.
     *                  In der Simulation wird dieser Wert nicht verwendet.
     */

    explicit BuzzerController(int buzzerPin);

    void playWarningTone();
    void playErrorTone();
    void stopTone();

    bool isPlaying() const;

private:
    int buzzerPin;  //simuliert Pin an dem Buzzer angeschlossen wäre
    bool playing;   //Ton gerade ja/nein
};

} // namespace ui

