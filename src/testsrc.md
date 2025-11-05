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
