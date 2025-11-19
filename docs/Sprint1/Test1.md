# Sprint 1 – Testfälle (Modul- & Integrationsebene)
_Eierkocher Trockenlaufschutz – Testprotokoll_

Dieses Dokument beschreibt die Testfälle gemäß Aufgabenstellung:

- 3 Modul-Testfälle (algorithmische Korrektheit)
- 3 Integrations-Testfälle (Zusammenarbeit von Modulen)
- Dokumentation der Testergebnisse
- Zuordnung zu Sprint 1

---

## 1. Modultests (Algorithmische Korrektheit)

### **M1 – Berechnung Füllstand in Prozent**
**Betroffene Requirements:** R1.1, R3.3  
**Modul:** FillLevelSensor  

**Vorbedingung:**  
- FillLevelSensor-Objekt existiert  
- Simulierter Rohwert 512 (10-bit ADC: 0–1023)

**Aktion:**  
- `getFillLevelPercent()` aufrufen

**Erwartetes Ergebnis:**  
- Rückgabe ≈ **50 % ± 5 %**

**Nachbedingung:**  
- Interner Messwert-Cache aktualisiert

**Ergebnis:**  
- ✔️ Test bestanden / ❌ Test fehlgeschlagen

---

### **M2 – Erkennung eines kritischen Temperaturanstiegs**
**Betroffene Requirements:** R1.2  
**Modul:** TemperatureSensor  

**Vorbedingung:**  
- Zwei Messwerte vorhanden:  
  - t0 = 40 °C  
  - t1 = 46 °C nach 1 Sekunde

**Aktion:**  
- `calculateDeltaT()` ausführen

**Erwartetes Ergebnis:**  
- ΔT = **6 °C/s**  
- Grenzwert > 5 °C/s wird erkannt

**Nachbedingung:**  
- Modulstatus "DeltaT kritisch" gesetzt

**Ergebnis:**  
- ✔️ / ❌

---

### **M3 – Heizungsabschaltung bei kritischem Füllstand**
**Betroffene Requirements:** R2.1, R3.1  
**Modul:** ControlLogic  

**Vorbedingung:**  
- Füllstand = 8 %  
- Keine Temperaturwarnung aktiv

**Aktion:**  
- `updateState(fillLevelPercent)` ausführen

**Erwartetes Ergebnis:**  
- Zustand = „Trockenlauf“  
- Heizung = **OFF**

**Nachbedingung:**  
- `heaterEnabled == false`

**Ergebnis:**  
- ✔️ / ❌

---

## 2. Integrationstests (Zusammenspiel der Module)

### **I1 – FillLevelSensor → ControlLogic**
**Betroffene Requirements:** R1.1, R2.1, R3.1  
**Komponenten:** FillLevelSensor, ControlLogic  

**Vorbedingung:**  
- Sensor liefert 5 % Füllstand

**Aktion:**  
- `control.update(fillSensor.getFillLevelPercent())`

**Erwartetes Ergebnis:**  
- Zustand = kritisch  
- Heizung = OFF

**Nachbedingung:**  
- Heizung deaktiviert

**Ergebnis:**  
- ✔️ / ❌

---

### **I2 – ControlLogic → DisplayController**
**Betroffene Requirements:** R5.1–R5.3  
**Komponenten:** ControlLogic, DisplayController  

**Vorbedingung:**  
- ControlLogic-Zustand = „Warnung“

**Aktion:**  
- `display.updateState(control.getState())`

**Erwartetes Ergebnis:**  
- Gelber Warnstatus sichtbar  
- Füllstandsanzeige korrekt  
- Kein rotes/blinkendes Symbol

**Nachbedingung:**  
- Displaystatus aktualisiert

**Ergebnis:**  
- ✔️ / ❌

---

### **I3 – ControlLogic → HeaterController**
**Betroffene Requirements:** R3.1  
**Komponenten:** ControlLogic, HeaterController  

**Vorbedingung:**  
- Temperaturanstieg > 5 °C/s wurde erkannt

**Aktion:**  
- `heater.off()` wird aufgerufen

**Erwartetes Ergebnis:**  
- Ausgangspin LOW  
- Heizung aus

**Nachbedingung:**  
- `heater.isOn() == false`

**Ergebnis:**  
- ✔️ / ❌

---

## 3. Zusammenfassung Sprint-1-Testresultate

| Test-ID | Titel                         | Ergebnis     |
|---------|--------------------------------|--------------|
| M1      | Füllstandskalkulation          | ✔️ / ❌ |
| M2      | Temperaturanstieg-Erkennung    | ✔️ / ❌ |
| M3      | Heizungsabschaltung            | ✔️ / ❌ |
| I1      | Sensor → ControlLogic          | ✔️ / ❌ |
| I2      | ControlLogic → Display         | ✔️ / ❌ |
| I3      | ControlLogic → Heater          | ✔️ / ❌ |

---
