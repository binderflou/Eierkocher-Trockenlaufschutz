# Architektur 

# Softwarearchitektur – kompakte Schichtenübersicht

```mermaid
graph TD
    %% Schichten
    subgraph Sensordatenerfassung
        FILL[Füllstand]
        TEMP[Temperatur]
        TIME[Zeit]
    end

    subgraph Verarbeitung
        DAT[Sensorverarbeitung]
        STATUS[Auswertelogik]
    end

    subgraph Steuerung
        HEAT[Heizung]
        SAFETY[Sicherheitsmodus]
    end

    subgraph UI
        DISPLAY[Anzeige & Warnungen]
    end

    %% Datenflüsse
    FILL --> DAT
    TEMP --> DAT
    TIME --> DAT
    DAT --> STATUS
    STATUS --> HEAT
    STATUS --> SAFETY
    STATUS --> DISPLAY

```

# Softwarearchitektur – Komponenten, Aufgaben & Requirements

| **Komponente**           | **Aufgaben**                                                                 | **Zugeordnete Requirements** |
|---------------------------|----------------------------------------------------------------------------|-----------------------------|
| **Füllstandssensor**      | Misst Füllstand, prüft Sensorfehler, liefert Werte an Verarbeitung          | R1.1                        |
| **Temperatursensor**      | Misst Heizplattentemperatur, erkennt Überhitzung                            | R1.2                        |
| **RTC/Timer**             | Liefert Zeitstempel für Soll/Ist-Vergleich und Sensorabfragen              | R1.3                        |
| **Sensorverarbeitung**    | Glättung der Messwerte, Temperaturkompensation, Berechnung tatsächlicher Füllstand | R3.3                        |
| **Auswertelogik**         | Vergleich Soll/Ist, Erkennung von Normal/Warnung/Kritisch, Weitergabe an Steuerung & UI | R2.1                        |
| **Heizung**               | Aktivierung/Deaktivierung der Heizung, Umsetzung der Sicherheitsregeln      | R3.1                        |
| **Sicherheitsmodus**      | Trockenlaufschutz, Abschaltung bei kritischen Sensorwerten                 | R3.1                        |
| **Anzeige & Warnungen**   | Darstellung von Füllstand & Temperatur, Anzeige von Warnungen und Fehlern    | R5.1, R5.2                  |
