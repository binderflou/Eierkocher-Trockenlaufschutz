# Architektur 

## Softwarearchitektur Übersicht

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


# Softwarearchitektur – Schichtenübersicht

```mermaid
graph TD
    %% Schicht: Sensordatenerfassung
    subgraph Sensordatenerfassung
        FILL[Füllstandssensor]
        TEMP[Temperatursensor]
        TIME[RTC/Timer]
    end

    %% Schicht: Datenverarbeitung & Zustandsüberwachung
    subgraph Datenverarbeitung
        DAT[Sensor-Datenverarbeitung]
        SIV[Soll/Ist-Vergleich]
        STATUS[Statusbestimmung: Normal / Warnung / Kritisch]
    end

    %% Schicht: Steuerlogik & Sicherheit
    subgraph Steuerlogik
        HEAT[Heizungssteuerung]
        SAFETY[Trockenlaufschutz / Sicherheitsmodus]
    end

    %% Schicht: Benutzerinterface
    subgraph Benutzerinterface
        DISPLAY_FILL[Füllstandsanzeige]
        DISPLAY_TEMP[Temperaturanzeige]
        WARN[Fehler- und Warnsignalmodul]
    end

    %% Schicht: Test & Diagnose
    subgraph Test_und_Diagnose
        TEST[Selbsttest & Plausibilitätsprüfung]
    end

    %% Datenflüsse zwischen den Schichten
    FILL --> DAT
    TEMP --> DAT
    TIME --> DAT
    DAT --> SIV
    SIV --> STATUS
    STATUS --> HEAT
    STATUS --> SAFETY
    DAT --> DISPLAY_FILL
    DAT --> DISPLAY_TEMP
    STATUS --> WARN
    TEST --> DAT
    TEST --> SIV
    TEST --> WARN
