Eierkocher-Trockenlaufschutz/
│
├── src/                                 # Quellcode des Projekts
│   │
│   ├── main.cpp                         # Einstiegspunkt (setup / loop)
│   │
│   ├── UserInterface/                   # Benutzeroberfläche
│   │   ├── DisplayController.cpp
│   │   ├── DisplayController.h
│   │   ├── BuzzerController.cpp
│   │   ├── BuzzerController.h
│   │   ├── InputHandler.cpp
│   │   ├── InputHandler.h
│   │
│   ├── Steuerungslogik/                 # Hauptsteuerung & Sicherheitslogik
│   │   ├── SystemController.cpp
│   │   ├── SystemController.h
│   │   ├── SafetyManager.cpp
│   │   ├── SafetyManager.h
│   │   ├── StateDetector.cpp
│   │   ├── StateDetector.h
│   │   ├── ThresholdManager.cpp
│   │   ├── ThresholdManager.h
│   │
│   ├── HardwareAbstraction/             # Sensorik & Aktorik
│   │   ├── FillLevelSensor.cpp
│   │   ├── FillLevelSensor.h
│   │   ├── TemperatureSensor.cpp
│   │   ├── TemperatureSensor.h
│   │   ├── HeaterControl.cpp
│   │   ├── HeaterControl.h
│   │   ├── TimerService.cpp
│   │   ├── TimerService.h
│   │
│   ├── PersistenceManager/              # Datenspeicherung & Kalibrierung
│   │   ├── SettingsStorage.cpp
│   │   ├── SettingsStorage.h
│   │   ├── CalibrationData.cpp
│   │   ├── CalibrationData.h
│   │
│   └── utils/                           # Hilfsfunktionen / Logging
│       ├── Logger.cpp
│       ├── Logger.h
│
├── test/                                # Unit- und Integrationstests
│   ├── test_UserInterface.cpp
│   ├── test_Steuerungslogik.cpp
│   ├── test_HardwareAbstraction.cpp
│   ├── test_PersistenceManager.cpp
│
├── diagrams/                            # UML- und Architekturdiagramme
│   ├── Klassendiagramm.puml
│   ├── Kommunikationsdiagramm.puml
│   ├── Sequenzdiagramm_Trockenlauf.puml
│
├── docs/                                # Projektdokumentation
│   ├── Pflichtenheft.md
│   ├── SoftwareDesign.md
│   ├── TraceabilityMatrix.md
│
└── README.md                            # Projektübersicht, Build-Hinweise

## Modulstruktur

```mermaid
%%==========================================
%% Modulstruktur – Trockenlaufschutz für Eierkocher
%%==========================================
graph TD

%% ======================
%% Hauptkomponenten
%% ======================
UI["🟦 UserInterface<br>(Anzeige & Eingabe)"]
LOGIC["🟨 Steuerungslogik<br>(System- & Sicherheitslogik)"]
HW["🟥 HardwareAbstraction<br>(Sensorik & Aktorik)"]
DATA["🟪 PersistenceManager<br>(Speicherung & Kalibrierung)"]
UTILS["⚙️ Utils<br>(Hilfsfunktionen / Logging)"]

%% ======================
%% Submodule
%% ======================

%% UserInterface
subgraph UI_Comp["UserInterface"]
    DC["DisplayController"]
    BC["BuzzerController"]
    IH["InputHandler"]
end

%% Steuerungslogik
subgraph Logic_Comp["Steuerungslogik"]
    SC["SystemController (Singleton)"]
    SM["SafetyManager"]
    SD["StateDetector"]
    TM["ThresholdManager"]
end

%% HardwareAbstraction
subgraph HW_Comp["HardwareAbstraction"]
    FS["FillLevelSensor"]
    TS["TemperatureSensor"]
    HC["HeaterControl"]
    TR["TimerService"]
end

%% PersistenceManager
subgraph Data_Comp["PersistenceManager"]
    SS["SettingsStorage"]
    CD["CalibrationData"]
end

%% Utils
subgraph Utils_Comp["Utils"]
    LG["Logger"]
end

%% ======================
%% Beziehungen
%% ======================
UI --> LOGIC
LOGIC --> HW
LOGIC --> DATA
LOGIC --> UI
HW --> DATA
LOGIC --> UTILS

%% ======================
%% Layoutanpassung
%% ======================
classDef comp fill:#f9f9f9,stroke:#444,stroke-width:1px;
classDef layer fill:#f1f1f1,stroke:#888,stroke-width:2px;
class UI,LOGIC,HW,DATA,UTILS layer
