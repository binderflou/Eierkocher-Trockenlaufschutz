# Implementierung
## Erweiterte Traceability Matrix (inkl. Implementierungsstatus & Testfälle)

| **Req-ID** | **Beschreibung** | **Modul** | **Zugehörige Klassen** | **Methoden / Schnittstellen** | **Bearbeitung in Sprint** | **Implementierung** | **Testfälle** |
|-----------|------------------|----------------------|-------------------------|-------------------------------|---------------------------|----------------------|----------------|
| **R1.1** | Füllstandsmessung, Genauigkeit, Sensorfehler | HardwareAbstraction | `FillLevelSensor`, `TimerService` | `readLevel()` `isValid()` | 1 | `readLevel()` `isValid()` | M1, I1 (bestanden) |
| **R1.2** | Temperaturmessung, ΔT-Erkennung, Überhitzung | HardwareAbstraction | `TemperatureSensor`, `TimerService` | `readTemperature()` `getDeltaT()` | 1 | `readTemperature()` `getDeltaT()` | M2 (bestanden) |
| **R1.3** | Zeitmessung, Messintervall | HardwareAbstraction | `TimerService` | `elapsed(ms)` | 1 | `elapsed()` | (über I-Tests) (bestanden) |
| **R2.1** | Auswertung Sensorwerte, Statuswechsel | ControlLogic | `SystemController`, `StateDetector` | `updateSystemState()` `detectState()` | 1 | `updateSystemState()` `detectState()` | M3, I1 (bestanden) |
| **R2.2** | Kontinuierlicher Soll/Ist-Vergleich, Sicherheitsmodus | ControlLogic | `SystemController`, `SafetyManager` | `executeCycle()` `checkDryRun()` | 1/2 | `executeCycle()` `checkDryRun()` | I1, I3, M4, I5 (bestanden) |
| **R2.3** | Fehleranalyse: Sensorfehler, Überhitzung | ControlLogic | `SafetyManager`, `StateDetector` | `checkDryRun()` | 2 | `checkDryRun()` | M4, I5, I6 (bestanden) |
| **R3.1** | Heizungsabschaltung (<10 %, ΔT>5 °C/s) | ControlLogic / HardwareAbstraction | `HeaterControl`, `SafetyManager` | `switchOffHeater()` | 1 | `switchOffHeater()` | M3, I3 (bestanden) |
| **R3.2** | Warnungen: Anzeigewechsel, akustisches Signal | UserInterface | `DisplayController`, `BuzzerController` | `updateDisplay()` `playErrorTone()` | 1 | `updateDisplay()` `playErrorTone()`  | I2 (bestanden)|
| **R3.3** | Berechnung tatsächlicher Füllstand | ControlLogic | `SystemController`, `ThresholdManager` | `updateSystemState()` `setWarningThreshold()` | 1 | `updateSystemState()` `setWarningThreshold()` | M1 (bestanden) |
| **R4.1** | Plausibilitätsprüfung beim Einschalten | ControlLogic / HardwareAbstraction | `SystemController`, `FillLevelSensor`, `TemperatureSensor` | `readLevel()`, `readTemperature()` | 2 | `readLevel()` `readTemperature` | M5, I4 (bestanden) |
| **R4.2** | Fehlerklassifizierung | ControlLogic / UI | `SafetyManager`, `DisplayController` | `checkDryRun()` `showWarning()` | 2 | `checkDryRun()` `showWarning()` | M4, I4, I5 (bestanden) |
| **R4.3** | Zyklischer Selbsttest (30s) | ControlLogic | `SystemController`, `SafetyManager` | `executeCycle()` `handleError()` | 2 | `executeCycle()` `handleError()` | M6, I6 (bestanden) |
| **R5.1** | Füllstandsanzeige (500 ms) | UserInterface | `DisplayController` | `updateDisplay(fillLevel)` | 1 | `updateDisplay(fillLevel)` | I2 (bestanden) |
| **R5.2** | Temperaturanzeige | UserInterface | `DisplayController` | `updateDisplay(temperature)` | 1 | `updateDisplay(temperature)` | I2 (bestanden) |
| **R5.3** | Warnanzeige | UserInterface | `DisplayController` | `updateDisplay(status)` | 3 | `updateDisplay(status)` | I2, M9, I10 (bestanden) |
| **R5.4** | Fehlermeldung Trockenlauf, Quittierung | UI / ControlLogic | `DisplayController`, `SystemController` | `showWarning()` `acknowledgeError()` | 3 | `showWarning()` | M7, M8, I7, I8, I9 (bestanden) |
| **R5.5** | Akustisches Warnsignal | UserInterface | `BuzzerController` | `playWarningTone()` `playErrorTone()` | 3 | `playWarningTone()` `playErrorTone()` | I7, I9, I10 (bestanden) |
| **R5.6** | Einstellbare Warnschwelle | UI / ControlLogic / PersistenceManager | `InputHandler`, `ThresholdManager`, `SettingsStorage` | `readInput()`, `setWarningThreshold()` | 3 | `readInput()`, `setWarningThreshold()` | M10, I10 (bestanden) |