%% Trockenlaufschutz – Komponentendiagramm
%% Mermaid UML Diagramm (Version 10+ empfohlen)

graph LR
    %% Sensorik-Komponenten
    subgraph Sensorik
        FS[Füllstandssensor]
        TS[Temperatursensor]
        TM[Timer / RTC]
    end

    %% Auswertelogik-Komponenten
    subgraph Auswertelogik
        FL[SensorManager\n- liest & filtert Sensordaten]
        EV[EvaluationLogic\n- bestimmt Betriebszustand]
    end

    %% Steuerlogik-Komponenten
    subgraph Steuerlogik
        CT[ControlLogic\n- Sicherheitsabschaltung, Relaissteuerung]
        ST[SelfTestManager\n- Start- & Plausibilitätsprüfung]
        TI[TimerService\n- Zeitbasis für Tasks]
    end

    %% Benutzerinterface-Komponenten
    subgraph Benutzerinterface
        DI[DisplayController\n- Anzeige von Werten & Fehlern]
        BU[BuzzerController\n- Akustische Warnungen]
        IN[InputHandler\n- Taster / Encoder-Eingaben]
    end

    %% Verbindungen
    FS --> FL
    TS --> FL
    TM --> TI
    FL --> EV
    EV --> CT
    ST --> CT
    IN --> CT
    CT --> DI
    CT --> BU
    CT --> FS
    CT --> TS

    %% externe Aktoren
    CT -->|Relaissteuerung| HE[Heizelement]
