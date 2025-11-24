# Sprint 1

## Sprint 1 Planung

Im ersten Sprint werde ich mich darauf konzentrieren, die Basisfunktionalitäten zu bearbeiten. Ich erhoffe mir dadurch am Ende des Sprints einen
laufähigen Prototypen zu erhalten. Konkret wurden folgende Kernfunktionaliäten ausgewählt:
- korrektes Einlesen der Sensorwerte (simuliert)
- Verarbeitung und Anzeige selbiger
- Abschaltung bei kritischem Füllstand

Dazu gehören folgende Requirements:
- R1.1  Füllstandsmessung
- R1.2  Temperaturmessung
- R1.3  Zeitmessung
- R2.1  Auswertung Sensorwerte
- R3.1  Heizungssteuerung
- R3.3  Berechnung Füllstand
- R5.1  Füllstandsanzeige
- R5.2  Temperaturanzeige

## Retrospektive

| Geplant (Architektur / Design)                                         | Implementiert in Sprint 1                                   | Abweichung                                                |
| ------------------------------------------------------------------- | ----------------------------------------------------------- | --------------------------------------------------------- |
| **InputHandler** soll z. B. „OK“-Taste anbieten                     | Implementiert als Toggle-Simulation (jede Sekunde Wechsel)  | Nicht UI-realistisch, nicht wie in Req. beschrieben |
| **TemperatureSensor** soll Temperatur kontinuierlich messen         | Tatsächlich steigt die Temperatur in 25°C Sprüngen          | Simulation nicht realistisch                              |
| **BuzzerController** soll akustische Signale steuern                | Implementiert nur bool-Flag (Simulation)                    | Nicht kritisch, aber Abweichung von echter Funktionalität |
| **FillLevelSensor** soll reale Messung simulieren                   | Implementiert als Reset nach 0 %                            | Unrealistisches Verhalten bei Simulation  |
| **TimerService** zentrale Instanz, gemeinsame Zeitquelle            | Zwei Instanzen `timerServiceFill`, `timerServiceTemp`       | anders geplant, Implementierung war (meinem Kenntnisstand nach) nicht anders möglich |

# Was lief gut?
- Alle ausgewählten Requirements für Sprint 1 wurden in Sprint 1 erledigt
- Tests wurden erfolgreich durchgeführt
- An der gewählten Architektur konnte festgehalten werden
- Klassendiagramm konnte in Code überführt werden
- Code wurde konsequent kommentiert

# Was lief nicht gut?
- Erstellung UML Diagramme sehr aufwendig
- Startpunkt für Programmierung hat gefehlt
- Programmierung hatte keinen roten Faden, es wurde einfach drauf los programmiert
- Schwierig von 0 zu beginnen, Einarbeitung in Tools zeitintensiv
- Aktualisierung Traceability Matrix erfolgte nicht automatisch

# Lessons Learned
- nicht von der Vielzahl an Anforderungen überfordern lassen
- Startpunkt für Programmierung festlegen
- Traceability Matrix konsequent pflegen
- Sensorsimulation ist rudimentär

# Baseline Sprint 1
- funktionierenden Kernablauf (lesen, state, warnen, schalten)
- UI und Buzzer rudimentär vorhanden
- Funktionierende Simulation der Sensoren
- Safety nur als „Trockenlauf“ verfügbar
