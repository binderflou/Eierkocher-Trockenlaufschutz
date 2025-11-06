# Implementierung
## Traceability Matrix

| **Requirement ID** | **Requirement Beschreibung** | **Systemkomponente** | **Zugehörige Klassen** | **Schnittstellen / Methoden** | **Bearbeitung in Sprint** |
|--------------------|------------------------------|----------------------|-------------------------|-------------------------------|---------------------------|
| **R1.1** | Füllstandsmessung: 0–250 ml, Auflösung ≤5 %, Reaktionszeit ≤500 ms, Sensorfehlererkennung, Genauigkeit ±5 % | HardwareAbstraction | `FillLevelSensor`, `TimerService` | `readLevel()`, `isValid()` | 1 |
| **R1.2** | Temperaturmessung: 0–150 °C, Genauigkeit ±1 °C, Abtastrate ≥5 Hz, Überhitzungserkennung, Sicherheitsabschaltung >110 °C | HardwareAbstraction | `TemperatureSensor`, `TimerService` | `readTemperature()`, `getDeltaT()` | 1 |
| **R1.3** | Zeitmessung: interne Echtzeituhr ±0,1 s, Messintervall ≤200 ms | HardwareAbstraction | `TimerService` | `elapsed(ms)` | 1 |
| **R2.1** | Auswertung Sensorwerte: Sollwertvergleich, Statuswarnung bei Abweichung >10 %, Berechnungszyklus ≤500 ms | ControlLogic | `SystemController`, `StateDetector` | `updateSystemState()`, `detectState()` | 1 |
| **R2.2** | Vergleich Soll/Ist kontinuierlich, Update ≥2×/s, Sicherheitsmodus bei fehlendem Messwert | ControlLogic | `SystemController`, `SafetyManager` | `executeCycle()`, `checkDryRun()` |  |
| **R2.3** | Fehleranalyse: Sensorfehler, Überhitzung | ControlLogic | `SafetyManager`, `StateDetector` | `checkDryRun()`, `handleError()` |  |
| **R3.1** | Heizungssteuerung: Abschalten bei Füllstand <10 % oder Temperaturanstieg >5 °C/s, Reaktionszeit ≤1 s | HardwareAbstraction / ControlLogic | `HeaterControl`, `SafetyManager` | `switchOffHeater()`, `emergencyShutdown()` | 1 |
| **R3.2** | Warnungen: Anzeigewechsel ≤300 ms, akustisches Signal bei kritischem Zustand, Wiederholung alle 10 s | UserInterface | `DisplayController`, `BuzzerController` | `updateDisplay()`, `playErrorTone()` |  |
| **R3.3** | Berechnung tatsächlicher Füllstand: Sensordaten + Temperaturkompensation, Berechnungszeit ≤100 ms | ControlLogic | `SystemController`, `ThresholdManager` | `updateSystemState()`, `setWarningThreshold()` | 1 |
| **R4.1** | Plausibilitätsprüfung beim Einschalten: Temperatur 0–50 °C, Füllstand 0–100 %, Dauer ≤2 s | ControlLogic / HardwareAbstraction | `SystemController`, `FillLevelSensor`, `TemperatureSensor` | `validate()`, `readLevel()`, `readTemperature()` |  |
| **R4.2** | Fehlerklassifizierung: Warnung (Füllstand <20 %), Fehler (Trockenlauf), Kritisch (Sensorfehler/Überhitzung), Anzeige <300 ms | ControlLogic / UserInterface | `SafetyManager`, `DisplayController` | `checkDryRun()`, `showWarning()` |  |
| **R4.3** | Zyklischer Selbsttest: alle 30 s, unveränderte Werte >10 s → Plausibilitätswarnung | ControlLogic | `SystemController`, `SafetyManager` | `executeCycle()`, `handleError()` |  |
| **R5.1** | Füllstandsanzeige: 0–100 %, Aktualisierung alle 500 ms, Genauigkeit ±5 % | UserInterface | `DisplayController` | `updateDisplay(fillLevel)` | 1 |
| **R5.2** | Temperaturanzeige: 0–120 °C, Aktualisierung alle 500 ms, Genauigkeit ±5 % | UserInterface | `DisplayController` | `updateDisplay(temperature)` | 1 |
| **R5.3** | Warnanzeige: Farbcode (Grün/Gelb/Rot), Helligkeit <300 cd/m², Symbole bei Farbfehlsichtigkeit | UserInterface | `DisplayController` | `updateDisplay(status)` |  |
| **R5.4** | Fehlermeldung bei Trockenlauf: Text, Anzeige aktiv bis quittiert | UserInterface / ControlLogic | `DisplayController`, `SystemController` | `showWarning()`, `acknowledgeError()` |  |
| **R5.5** | Akustische Signalisierung: 60–80 dB(A), Signaltyp 2× kurz bei Warnung, 3× lang bei Fehler, Reaktionszeit ≤500 ms | UserInterface | `BuzzerController` | `playWarningTone()`, `playErrorTone()` |  |
| **R5.6** | Schwelle einstellen: benutzerdefinierbare Warnwerte | UserInterface / ControlLogic / PersistenceManager | `InputHandler`, `ThresholdManager`, `SettingsStorage` | `readInput()`, `setWarningThreshold()`, `saveSettings()` |  |

---

