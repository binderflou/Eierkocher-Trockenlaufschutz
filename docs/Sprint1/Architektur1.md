# Architektur 
## Softwarearchitektur Trockenlaufschutz 

# Softwarearchitektur – Wasser-/Heizsystem

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
