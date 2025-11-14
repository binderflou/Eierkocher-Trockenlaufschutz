#pragma once

namespace hardware {

 /**
 * @brief Simulierte Steuerung des Heizrelais / MOSFET.
 *
 * In der echten Hardware würde diese Klasse ein Relais oder MOSFET schalten,
 * der die Heizplatte ein- oder ausschaltet.
 */
class HeaterControl {
public:
    /**
    * @brief Konstruktor
    * @param relayPin Pin-Nummer, an dem das Relais/MOSFET angeschlossen wäre.
    */
    explicit HeaterControl(int relayPin);
    //Schaltet Heizung EIN
    void switchOn();
    //Schaltet Heizung AUS
    void switchOff();
    //gibt zurück ob Heizung gerade EIN/AUS
    bool getStatus() const;

private:
    int relayPin;   //Simuliert Pin an dem Relais angeschlossen wäre
    bool isOn;  //akt. Heizstatus
};

} // namespace hardware

