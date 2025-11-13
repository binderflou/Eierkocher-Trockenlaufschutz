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
        controller.executeCycle();

        int currentFillLevel = displayController.getFillLevelDisplay();
        int currentTemperature = displayController.getTemperatureDisplay();
        std::string currentState = stateDetector.getState();
        std::string warningMessage = displayController.getWarningMessage();
        bool heaterState = heaterControl.getStatus();
        bool buzzerState = buzzerController.isPlaying();

        std::cout << "[Zyklus " << cycle++ << "] Fuellstand: " << currentFillLevel
                  << "% | Temperatur: " << currentTemperature
                  << "°C | Zustand: " << currentState
                  << " | Heizung: " << (heaterState ? "AN" : "AUS");

        if (!warningMessage.empty()) {
            std::cout << " | Warnung: " << warningMessage;
        }

        if (buzzerState) {
            std::cout << " | Buzzer aktiv";
        }

        std::cout << std::endl;

        if (warningMessage != previousWarning) {
            if (!warningMessage.empty()) {
                std::cout << "  -> Neues Ereignis: Warnung '" << warningMessage
                          << "'" << std::endl;
            } else {
                std::cout << "  -> Ereignis: Warnung quittiert" << std::endl;
            }
            previousWarning = warningMessage;
        }

        if (currentState != previousState) {
            std::cout << "  -> Systemzustand geaendert zu '" << currentState
                      << "'" << std::endl;
            previousState = currentState;
        }

        if (heaterState != previousHeaterState) {
            std::cout << "  -> Heizung wurde "
                      << (heaterState ? "eingeschaltet" : "ausgeschaltet")
                      << std::endl;
            previousHeaterState = heaterState;
        }

        if (buzzerState != previousBuzzerState) {
            std::cout << "  -> Buzzer "
                      << (buzzerState ? "gestartet" : "gestoppt") << std::endl;
            previousBuzzerState = buzzerState;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}

