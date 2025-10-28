# Architektur 

## Softwarearchitektur Übersicht

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


## Softwarearchitektur Trockenlaufschutz 

```mermaid
graph TD
    %% Sensordatenerfassung
    FILL[Füllstandssensor] --> DAT[Sensor-Datenverarbeitung]
    TEMP[Temperatursensor] --> DAT
    TIME[RTC/Timer] --> DAT

    %% Datenverarbeitung & Zustandsüberwachung
    DAT --> SIV[Soll/Ist-Vergleich]
    SIV --> STATUS[Statusbestimmung: Normal / Warnung / Kritisch]

    %% Steuerlogik & Sicherheit
    STATUS --> HEAT[Heizungssteuerung]
    STATUS --> SAFETY[Trockenlaufschutz / Sicherheitsmodus]

    %% Benutzerinterface
    DAT --> DISPLAY_FILL[Füllstandsanzeige]
    DAT --> DISPLAY_TEMP[Temperaturanzeige]
    STATUS --> WARN[Fehler- und Warnsignalmodul]

    %% Test- und Diagnosemodul
    TEST[Selbsttest & Plausibilitätsprüfung] --> DAT
    TEST --> SIV
    TEST --> WARN

    %% Benutzer / Externe Schnittstellen
    USER[Benutzer] --> DISPLAY_FILL
    USER --> DISPLAY_TEMP
    USER --> WARN
