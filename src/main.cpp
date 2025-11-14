#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "hardwareAbstraction/FillLevelSensor.h"
#include "hardwareAbstraction/HeaterControl.h"
#include "hardwareAbstraction/TemperatureSensor.h"
#include "hardwareAbstraction/TimerService.h"
#include "persistenceManager/CalibrationData.h"
#include "persistenceManager/SettingsStorage.h"
#include "steuerungsLogik/SafetyManager.h"
#include "steuerungsLogik/StateDetector.h"
#include "steuerungsLogik/SystemController.h"
#include "steuerungsLogik/ThresholdManager.h"
#include "userInterface/BuzzerController.h"
#include "userInterface/DisplayController.h"
#include "userInterface/InputHandler.h"

int main() {
    std::cout << "\n=== Eierkocher Trockenlauf-Simulation ===\n";
    std::cout << "Initialisiere Komponenten..." << std::endl;
    
    // Je Sensor ein eigener TimerService, damit deren Zeitmessungen
    // sich nicht gegenseitig beeinflussen.
    auto timerServiceFill = std::make_shared<hardware::TimerService>();
    auto timerServiceTemp = std::make_shared<hardware::TimerService>();
    
    // Die Hardware-Klassen simulieren interne Werte. Konkrete Pins werden nicht benötigt.
    hardware::FillLevelSensor fillLevelSensor(0, timerServiceFill);
    hardware::TemperatureSensor temperatureSensor(0, timerServiceTemp);
    hardware::HeaterControl heaterControl(0);

    ui::DisplayController displayController;
    ui::BuzzerController buzzerController(0);
    ui::InputHandler inputHandler(0);

    logic::StateDetector stateDetector;
    logic::SafetyManager safetyManager;
    logic::ThresholdManager thresholdManager;
    persistence::SettingsStorage settingsStorage;

    //zentrale Steuerlogik, in der alle Komponenten zusammenspielen
    logic::SystemController controller(fillLevelSensor, temperatureSensor,
                                       heaterControl, displayController,
                                       buzzerController, inputHandler,
                                       stateDetector, safetyManager,
                                       thresholdManager, settingsStorage);

    std::cout << "Simulation gestartet. Druecken Sie Strg+C zum Beenden." << std::endl;

    int cycle = 0;
    std::string previousWarning;
    std::string previousState = stateDetector.getState();
    bool previousHeaterState = heaterControl.getStatus();
    bool previousBuzzerState = buzzerController.isPlaying();

    while (true) {
        // Ein Steuerungszyklus: Sensoren lesen, Logik ausführen, Display/Buzzer steuern
        controller.executeCycle();

        // Werte aus der Display-Simulation abfragen (für Konsolenausgabe)
        int currentFillLevel = displayController.getFillLevelDisplay();
        int currentTemperature = displayController.getTemperatureDisplay();
        std::string currentState = stateDetector.getState();
        std::string warningMessage = displayController.getWarningMessage();
        bool heaterState = heaterControl.getStatus();
        bool buzzerState = buzzerController.isPlaying();

        std::cout << "[Zyklus " << cycle++ << "] Fuellstand: " << currentFillLevel
                  << "% | Temperatur: " << currentTemperature
                  << "C | Zustand: " << currentState
                  << " | Heizung: " << (heaterState ? "AN" : "AUS");
        
        if (!warningMessage.empty()) {
            std::cout << " | Warnung: " << warningMessage;
        }

        if (buzzerState) {
            std::cout << " | Buzzer aktiv";
        }

        std::cout << std::endl;
        
        //Ereignis-Logging Warnungswechsel
        if (warningMessage != previousWarning) {
            if (!warningMessage.empty()) {
                std::cout << "  -> Neues Ereignis: Warnung '" << warningMessage
                          << "'" << std::endl;
            } else {
                std::cout << "  -> Ereignis: Warnung quittiert" << std::endl;
            }
            previousWarning = warningMessage;
        }

        //Ereignis Logging für Zustandswechsel
        if (currentState != previousState) {
            std::cout << "  -> Systemzustand geaendert zu '" << currentState
                      << "'" << std::endl;
            previousState = currentState;
        }

        //Ereignis Logging für Heizungszustand
        if (heaterState != previousHeaterState) {
            std::cout << "  -> Heizung wurde "
                      << (heaterState ? "eingeschaltet" : "ausgeschaltet")
                      << std::endl;
            previousHeaterState = heaterState;
        }

        //Ereignis Logging für Buzzerzustand
        if (buzzerState != previousBuzzerState) {
            std::cout << "  -> Buzzer "
                      << (buzzerState ? "gestartet" : "gestoppt") << std::endl;
            previousBuzzerState = buzzerState;
        }

        //Simulierter Zyklusabstand: 1 sek
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}

