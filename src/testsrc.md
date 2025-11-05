Eierkocher-Trockenlaufschutz/
│
├── src/
│   │
│   ├── main.cpp                         # Einstiegspunkt (setup/loop)
│   │
│   ├── UserInterface/                   # UI-Komponente
│   │   ├── DisplayController.cpp
│   │   ├── DisplayController.h
│   │   ├── BuzzerController.cpp
│   │   ├── BuzzerController.h
│   │   ├── InputHandler.cpp
│   │   ├── InputHandler.h
│   │
│   ├── Steuerungslogik/                 # Zentrale Logik-Komponente
│   │   ├── SystemController.cpp
│   │   ├── SystemController.h
│   │   ├── SafetyManager.cpp
│   │   ├── SafetyManager.h
│   │   ├── StateDetector.cpp
│   │   ├── StateDetector.h
│   │   ├── ThresholdManager.cpp
│   │   ├── ThresholdManager.h
│   │
│   ├── HardwareAbstraction/             # Hardwarezugriff & Sensorik
│   │   ├── FillLevelSensor.cpp
│   │   ├── FillLevelSensor.h
│   │   ├── TemperatureSensor.cpp
│   │   ├── TemperatureSensor.h
│   │   ├── HeaterControl.cpp
│   │   ├── HeaterControl.h
│   │   ├── TimerService.cpp
│   │   ├── TimerService.h
│   │
│   ├── PersistenceManager/              # Speicherung, Kalibrierung
│   │   ├── SettingsStorage.cpp
│   │   ├── SettingsStorage.h
│   │   ├── CalibrationData.cpp
│   │   ├── CalibrationData.h
│   │
│   └── utils/                           # Optional: Logging, Debug, Tools
│       ├── Logger.cpp
│       ├── Logger.h
│
├── test/                                # Testcode pro Komponente
│   ├── test_UserInterface.cpp
│   ├── test_Steuerungslogik.cpp
│   ├── test_HardwareAbstraction.cpp
│   ├── test_PersistenceManager.cpp
│
├── diagrams/                            # UML-Diagramme & Architektur
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

