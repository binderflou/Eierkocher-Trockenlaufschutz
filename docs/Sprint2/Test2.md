# Testfälle Sprint 2

Die folgenden Testfälle erweitern die bereits in Sprint 1 definierten Modul- und Integrationstests um sicherheitsrelevante Funktionen aus den Anforderungen R2.2, R2.3, R4.1, R4.2 und R4.3. Im Fokus stehen der kontinuierliche Soll/Ist-Vergleich, Fehleranalyse, Plausibilitätsprüfungen sowie Selbsttest-Mechanismen. Alle Tests wurden manuell (bzw. halb-manuell) in der IDE anhand der Sprint-2-Implementierung durchgeführt.

## Modultests (algorithmische Korrektheit)

### M4 – Fehlerklassifizierung im SafetyManager

- **Vorbedingung:**  
  SafetyManager ist initialisiert, interner Fehlerstatus steht auf „kein Fehler“. Schnittstellen für Fehlerquellen (z. B. Trockenlauf, Überhitzung, Sensorfehler, Plausibilitätsfehler) sind implementiert.

- **Aktion:**  
  1. SafetyManager mit folgenden Situationen füttern (z. B. über spezielle Prüfmethoden oder Flags):  
     - Fall A: `fillLevel = 3`, `tempRise = 6.0f` (Trockenlauf)  
     - Fall B: `fillLevel = 50`, `temperature = 130.0f` (Überhitzung)  
     - Fall C: Sensor liefert ungültige Werte (z. B. negativer Füllstand oder `isValid() = false`)  
  2. Jeweils nach der Prüfung die zurückgemeldete Fehlerklasse abfragen (z. B. `getLastErrorType()` o. ä.).

- **Erwartete Reaktion:**  
  - Fall A: Fehlerklasse „DryRun“ wird gesetzt.  
  - Fall B: Fehlerklasse „Overheat“ wird gesetzt.  
  - Fall C: Fehlerklasse „SensorError“ wird gesetzt.  
  In allen Fällen wird immer nur **ein eindeutiger Fehlercode** verwaltet.

- **Nachbedingung:**  
  - Interner Status speichert jeweils den zuletzt erkannten Fehler. Kein Mischzustand aus mehreren Fehlercodes.

- **Ergebnis Sprint 2:** Bestanden

---

### M5 – Plausibilitätsprüfung beim Einschalten (R4.1)

- **Vorbedingung:**  
  System befindet sich im Einschaltzustand; Plausibilitätslogik (z. B. im SafetyManager oder SystemController) ist implementiert.  
  Es gibt zwei definierte Szenarien:
  - Szenario 1 (plausibel): `fillLevel = 80 %`, `temperature = 20 °C`.  
  - Szenario 2 (unplausibel): `fillLevel = 0 %`, `temperature = 95 °C` oder Sensor meldet „ungültig“.

- **Aktion:**  
  1. Plausibilitätsfunktion für Szenario 1 aufrufen (z. B. beim ersten `executeCycle()` nach Systemstart).  
  2. Plausibilitätsfunktion für Szenario 2 aufrufen.

- **Erwartete Reaktion:**  
  - Szenario 1: Plausibilitätsprüfung gibt „OK“ zurück; kein Fehlercode gesetzt.  
  - Szenario 2: Plausibilitätsprüfung erkennt Inkonsistenz; Fehler wird als „StartupPlausibilityError“ (oder äquivalenter Typ) klassifiziert.

- **Nachbedingung:**  
  - Bei unplausiblem Zustand ist der Systemstart blockiert (z. B. Sicherheitsmodus aktiv, Heizung bleibt aus) und ein entsprechender Fehlerstatus ist gesetzt.

- **Ergebnis Sprint 2:** Bestanden

---

### M6 – Zyklischer Selbsttest-Trigger (R4.3)

- **Vorbedingung:**  
  Es existiert eine Logik, die alle 30 s einen Selbsttest auslöst (z. B. im SafetyManager oder einer eigenen SelfTest-Komponente), basierend auf einer Zeitbasis (TimerService o. ä.).  
  Letzter Selbsttest liegt „lange genug“ zurück.

- **Aktion:**  
  1. Zeitbasis so simulieren, dass mehrfach `elapsed(30000)` für den Selbsttestzeitraum erfüllt ist.  
  2. Bei jedem erfüllten Intervall die Selbsttestfunktion aufrufen (z. B. `runSelfTestIfDue()`).

- **Erwartete Reaktion:**  
  - Selbsttest wird genau dann ausgeführt, wenn das definierte Intervall überschritten ist.  
  - Zwischen zwei Intervallen wird kein zusätzlicher Selbsttest gestartet.

- **Nachbedingung:**  
  - Zähler/Zeitstempel für den letzten Selbsttest wird korrekt aktualisiert.  
  - Selbstteststatus (z. B. „SelfTestOK“ oder Fehlercode) ist abrufbar.

- **Ergebnis Sprint 2:** Bestanden

---

## Integrationstests (Aufrufsyntax und Zusammenarbeit)

### I4 – Plausibilitätsprüfung beim Einschalten mit UI-Rückmeldung (R4.1 + R4.2)

- **Vorbedingung:**  
  SystemController, SafetyManager, FillLevelSensor, TemperatureSensor, DisplayController und HeaterControl sind verdrahtet.  
  Anfangszustand: System frisch gestartet, Heizung noch AUS.  
  Sensoren liefern **unplausible Startwerte** (z. B. `fillLevel = 0 %`, `temperature = 95 °C` oder `isValid() = false`).

- **Aktion:**  
  - Ersten Steuerungszyklus ausführen: `executeCycle()` direkt nach dem Einschalten.

- **Erwartete Reaktion:**  
  - Plausibilitätsprüfung erkennt den Fehlerzustand.  
  - SafetyManager klassifiziert einen Plausibilitätsfehler („StartupPlausibilityError“).  
  - Heizung bleibt AUS.  
  - Display zeigt eine passende Fehlermeldung (z. B. „Sensor error“ oder „Startup plausibility error“).  
  - Buzzer kann optional einen Fehlerton auslösen.

- **Nachbedingung:**  
  - System befindet sich im Sicherheitsmodus / Fehlermodus und startet den normalen Heizbetrieb nicht, solange der Fehler anliegt.

- **Ergebnis Sprint 2:** Bestanden

---

### I5 – Überhitzungsfall: Fehleranalyse, Klassifizierung und Sicherheitsmodus (R2.2, R2.3, R4.2)

- **Vorbedingung:**  
  SystemController, TemperatureSensor, SafetyManager, HeaterControl, DisplayController und BuzzerController sind verbunden.  
  Füllstand ist normal (z. B. 50 %), aber die gemessene Temperatur steigt deutlich über den definierten Grenzwert (z. B. > 120 °C).

- **Aktion:**  
  - Mehrere Steuerungszyklen `executeCycle()` ausführen, bis die Temperatur den Überhitzungsbereich erreicht.

- **Erwartete Reaktion:**  
  - SafetyManager erkennt anhand der aktuellen Temperatur und ggf. ΔT eine Überhitzung.  
  - Fehler wird als „Overheat“ klassifiziert.  
  - System wechselt in einen Sicherheitsmodus (Heizung AUS, Fehlerstatus aktiv).  
  - `DisplayController` zeigt passende Fehlermeldung (z. B. „Overheat detected“).  
  - `BuzzerController` spielt Fehlerton.

- **Nachbedingung:**  
  - Heizung bleibt AUS, solange der Fehler nicht quittiert oder behoben ist.  
  - Fehlerstatus ist klar von Trockenlauf und anderen Fehlerarten unterscheidbar.

- **Ergebnis Sprint 2:** Bestanden

---

### I6 – Zyklischer Selbsttest deckt Sensorfehler auf (R2.3, R4.3)

- **Vorbedingung:**  
  Zeitgesteuerte Selbsttestlogik ist aktiv (z. B. alle 30 s).  
  System läuft im Normalbetrieb (kein aktueller Fehler).  
  Ein Sensor (z. B. FillLevelSensor) wird während des Betriebs in einen fehlerhaften Zustand versetzt (z. B. konstant gleicher Wert oder `isValid() = false`).

- **Aktion:**  
  1. System für eine simulierte Zeitspanne laufen lassen, bis der nächste Selbsttest fällig ist (mehrere `executeCycle()`-Aufrufe einschließlich Selbsttest).  
  2. Selbsttest wird ausgelöst.

- **Erwartete Reaktion:**  
  - Selbsttest erkennt den fehlerhaften Sensor (z. B. über Plausibilitätskriterien oder „keine Änderung über längere Zeit“).  
  - SafetyManager klassifiziert den Fehler als „SensorError“.  
  - System schaltet in sicheren Zustand: Heizung AUS.  
  - Display zeigt konkrete Fehlermeldung, Buzzer meldet Fehler.

- **Nachbedingung:**  
  - Fehlerklasse ist gesetzt und kann für Diagnose/Traceability genutzt werden.  
  - Normale Betriebslogik wird nicht fortgeführt, solange der Fehler aktiv ist.

- **Ergebnis Sprint 2:** Bestanden

