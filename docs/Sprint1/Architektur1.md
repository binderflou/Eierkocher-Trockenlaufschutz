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
        STATUS[Status]
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
