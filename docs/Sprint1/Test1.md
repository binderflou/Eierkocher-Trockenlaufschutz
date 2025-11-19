# Testfälle Sprint 1

Die folgenden Testfälle decken sowohl Modul- als auch Integrationsebene ab und orientieren sich an den Anforderungen des Systems. Jeder Testfall enthält Vorbedingung, Aktion, erwartete Reaktion, Nachbedingung und das beobachtete Ergebnis im Sprint-1-Durchlauf. Alle Tests wurden manuell in der IDE durchgeführt.

## Modultests (algorithmische Korrektheit)

### M1 – FillLevelSensor aktualisiert gültig und klemmt bei 0 %
- **Vorbedingung:** FillLevelSensor mit `fillLevelPercent = 100`, TimerService liefert bei jedem Aufruf `elapsed(50) = true`.
- **Aktion:** Zwei aufeinanderfolgende Aufrufe von `readLevel()`.
- **Erwartete Reaktion:** Der erste Aufruf setzt `valid = true` und reduziert den Füllstand auf 95 %, der zweite reduziert auf 90 %; kein Wert unter 0 %.
- **Nachbedingung:** `isValid()` liefert `true`, `readLevel()` gibt zuletzt 90 % zurück.
- **Ergebnis Sprint 1:** Bestanden

### M2 – TemperatureSensor begrenzt Temperaturanstieg und Delta-T
- **Vorbedingung:** TemperatureSensor mit `temperature = 20 °C`, TimerService liefert bei jedem Aufruf `elapsed(50) = true`.
- **Aktion:** Vier aufeinanderfolgende Aufrufe von `readTemperature()`.
- **Erwartete Reaktion:** Temperatur steigt in 25-°C-Schritten bis maximal 100 °C; `getDeltaT()` meldet den Anstieg zwischen den letzten beiden Aufrufen (maximal 25 °C).
- **Nachbedingung:** Temperaturwert ist auf 100 °C geklemmt, `getDeltaT()` entspricht dem letzten Schritt.
- **Ergebnis Sprint 1:** Bestanden

### M3 – SafetyManager erkennt Trockenlauf nur bei kombiniertem Grenzfall
- **Vorbedingung:** SafetyManager mit `dryRunDetected = false`.
- **Aktion:** Aufruf `checkDryRun(fillLevel = 3, tempRise = 6.0f)` gefolgt von `isDryRunDetected()`.
- **Erwartete Reaktion:** Methode liefert `true`, interner Status wird gesetzt.
- **Nachbedingung:** `isDryRunDetected()` ist `true`.
- **Ergebnis Sprint 1:** Bestanden

## Integrationstests (Aufrufsyntax und Zusammenarbeit)

### I1 – SystemController integriert Sensorwerte in Zustandsdetektion
- **Vorbedingung:** Instanzen von FillLevelSensor, TemperatureSensor und StateDetector sind verdrahtet; TimerService liefert gültige Takte; Startzustand `currentState = "Idle"`.
- **Aktion:** Aufruf `executeCycle()` mit initialem Füllstand 100 % und Temperatur 20 °C.
- **Erwartete Reaktion:** `updateSystemState()` ruft `StateDetector::detectState()` auf und setzt Zustand abhängig von Füllstand/Temperatur (anfangs „Heating“), ohne Fehlaufrufe der Sensor-APIs.
- **Nachbedingung:** `StateDetector::getState()` gibt den erwarteten Zustand zurück; keine Ausnahmen.
- **Ergebnis Sprint 1:** Bestanden

### I2 – Warnlogik steuert Anzeige und Buzzer bei Unterschreiten der Warnschwelle
- **Vorbedingung:** SystemController mit geladenen Schwellwerten (`warningThreshold` aus SettingsStorage), FillLevelSensor liefert Wert unter Warnschwelle aber über kritischer Schwelle, Heater ist betriebsbereit.
- **Aktion:** Aufruf `executeCycle()` während `fillLevel < warningThreshold` und `tempRise` im Normalbereich.
- **Erwartete Reaktion:** `heater.switchOn()` wird aufgerufen, `DisplayController::showWarning("Low fill level")` setzt Warntext, `BuzzerController::playWarningTone()` aktiviert Ton.
- **Nachbedingung:** Heizung ist EIN, Warntext gesetzt, Buzzer aktiv.
- **Ergebnis Sprint 1:** Bestanden

### I3 – Trockenlauferkennung erzwingt Notabschaltung und Fehlerkommunikation
- **Vorbedingung:** `SafetyManager::checkDryRun()` liefert `true` (z. B. `fillLevel = 3`, `tempRise = 6.0f`), Heater ist eingeschaltet, Display und Buzzer sind verbunden.
- **Aktion:** Aufruf `executeCycle()` in diesem Zustand.
- **Erwartete Reaktion:** `emergencyShutdown()` schaltet Heizung aus, `DisplayController::showWarning("Dry run detected")` setzt Fehlermeldung, `BuzzerController::playErrorTone()` wird aufgerufen.
- **Nachbedingung:** Heizung ist AUS, Fehlermeldung sichtbar, Fehlerton aktiv.
- **Ergebnis Sprint 1:** Bestanden
