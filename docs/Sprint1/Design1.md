# Design

# Softwarearchitektur – Design-Komponenten

```mermaid
graph TD
    %% Schicht 1: Sensordatenerfassung
    subgraph Sensordatenerfassung
        FILL[Füllstandsmessung]
        TEMP[Temperaturmessung]
        TIME[Zeitgeber]
    end

    %% Schicht 2: Datenverarbeitung & Zustandsüberwachung
    subgraph Verarbeitung
        DAT[Sensor-Datenverarbeitung]
        SIV[Soll/Ist-Vergleich]
        STATUS[Statusverwaltung]
    end

    %% Schicht 3: Steuerlogik & Sicherheit
    subgraph Steuerung
        HEAT[Heizungssteuerung]
        SAFETY[Trockenlaufschutz/Sicherheitsmodus]
    end

    %% Schicht 4: Benutzerinterface
    subgraph UI
        DISPLAY_FILL[Füllstandsanzeige]
        DISPLAY_TEMP[Temperaturanzeige]
        WARN[Warn- & Fehlermeldung]
    end

    %% Schicht 5: Test & Diagnose
    subgraph Test_und_Diagnose
        SELFTEST[Selbsttest & Plausibilitätsprüfung]
        ERROR[Fehleranalyse]
    end

    %% Datenflüsse zwischen den Komponenten
    FILL --> DAT
    TEMP --> DAT
    TIME --> DAT
    DAT --> SIV
    SIV --> STATUS
    STATUS --> HEAT
    STATUS --> SAFETY
    STATUS --> DISPLAY_FILL
    STATUS --> DISPLAY_TEMP
    STATUS --> WARN
    SELFTEST --> DAT
    SELFTEST --> SIV
    SELFTEST --> WARN
    ERROR --> STATUS
    ERROR --> WARN

