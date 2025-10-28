# Architektur 

graph TD
    %% Sensordatenerfassung
    A[Füllstandssensor] --> B[Sensor-Datenverarbeitung]
    C[Temperatursensor] --> B
    D[RTC/Timer] --> B

    %% Datenverarbeitung & Zustandsüberwachung
    B --> E[Soll/Ist-Vergleich]
    E --> F[Statusbestimmung: Normal / Warnung / Kritisch]

    %% Steuerlogik & Sicherheit
    F --> G[Heizungssteuerung]
    F --> H[Trockenlaufschutz / Sicherheitsmodus]

    %% Benutzerinterface
    B --> I[Füllstandsanzeige]
    B --> J[Temperaturanzeige]
    F --> K[Fehler- und Warnsignalmodul]

    %% Test- und Diagnosemodul
    L[Selbsttest & Plausibilitätsprüfung] --> B
    L --> F
    L --> K

    %% Externe Schnittstellen / Benutzer
    M[Benutzer] --> I
    M --> J
    M --> K

