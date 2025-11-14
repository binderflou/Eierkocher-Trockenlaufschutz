#pragma once

namespace ui {

/**
* @brief Simulierter Eingabeknopf (z.B. "OK"-Taste).
*
* In der Simulation wird der Button-Zustand bei jedem readInput()-Aufruf
* einfach umgeschaltet (toggle), um eine Benutzerinteraktion zu emulieren.
*/
class InputHandler {
public:
    /**
    * @brief Konstruktor
    * @param buttonPin Pin-Nummer, an dem die Taste im echten System hängen würde.
    */
    explicit InputHandler(int buttonPin);
    
    //liefert simulierte Eingabe (true=gedrückt)
    bool readInput();
    //gibt letzten bekannten Tastenstatus zurück
    bool isButtonPressed() const;

private:
    int buttonPin;  //simuliert Button Pin
    bool buttonState;   //akt. Zustandswert Taste
};

} // namespace ui

