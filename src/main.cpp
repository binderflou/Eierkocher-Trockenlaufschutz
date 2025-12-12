#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <windows.h>
#include <conio.h>

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

void clearConsole() {
    // Bildschirm löschen und Cursor nach oben links setzen
    std::cout << "\033[2J\033[H";
}

void setColor(int textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}

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
        
        if (_kbhit()) {
            int ch = _getch();

            if (ch == 'f' || ch == 'F') {
                controller.onFillPressed();
            }
            else if (ch == 'a' || ch == 'A') {
                controller.onAckPressed();
            }
            else if (ch == 'w' || ch == 'W') {
                setColor(14); // gelb
                std::cout << "\n\n[Eingabe] Neue Warnschwelle in % (10..50): ";
                setColor(7);

                int newThreshold;
                std::cin >> newThreshold;

                // Bereich einschränken
                if (newThreshold < 10) newThreshold = 10;
                if (newThreshold > 50) newThreshold = 50;

                // ThresholdManager + SettingsStorage aktualisieren
                thresholdManager.setWarningThreshold(newThreshold);
                settingsStorage.setWarningThreshold(newThreshold);
                settingsStorage.saveSettings();

                setColor(10); // grün
                std::cout << "\nWarnschwelle auf " << newThreshold << "% gesetzt.\n";
                setColor(7);

                // kurze Pause, damit man die Meldung sieht
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
            }
        }

        // Displaybereich "leeren" und Cursor nach oben setzen
        clearConsole();

        // Steuerungszyklus ausführen
        controller.executeCycle();

        // Werte aus der Display-Simulation abfragen
        int currentFillLevel = displayController.getFillLevelDisplay();
        int currentTemperature = displayController.getTemperatureDisplay();
        std::string displayStatus = displayController.getStatusText();
        std::string currentState = stateDetector.getState();
        std::string warningMessage = displayController.getWarningMessage();
        bool heaterState = heaterControl.getStatus();
        bool buzzerState = buzzerController.isPlaying();
        std::string buzzerTone = buzzerController.getToneDescription();

        // ===== "Live-Display" Block =====
        std::cout << "=== Eierkocher Trockenlauf-Simulation ===\n\n";
        std::cout << "Zyklus:         " << cycle++ << "\n";
        std::cout << "Tasten: [W] Warnschwelle setzen  [F] Fuellen  [A] OK/Restart \n";
        std::cout << "-----------------------------------------------\n";
        // Füllstand-Ampel basierend auf ThresholdManager
        int critical = thresholdManager.getCriticalThreshold();
        int warning = thresholdManager.getWarningThreshold();

        // Farben: 12 = rot, 14 = gelb, 10 = grün, 7 = Standard
        int color = 10; // grün als Default

        if (currentFillLevel <= critical) {
            color = 12; // rot = kritisch
        }
        else if (currentFillLevel <= warning) {
            color = 14; // gelb = niedrig
        }

        setColor(color);
        std::cout << "Fuellstand:      " << currentFillLevel << " %\n";
        setColor(7); // wieder auf Standard zurück

        //std::cout << "Fuellstand:     " << currentFillLevel << " %\n";
        std::cout << "Temperatur:     " << currentTemperature << " °C\n";
        std::cout << "Zustand:        " << currentState << "\n";
        std::cout << "Display:        " << displayStatus << "\n";
        std::cout << "Heizung:        " << (heaterState ? "AN" : "AUS") << "\n";
        std::cout << "Buzzer:         "
            << (buzzerState ? ("aktiv (" + buzzerTone + ")") : "aus") << "\n";

        if (!warningMessage.empty()) {
            std::cout << "Warnung:        " << warningMessage << "\n";
        }

        std::cout << "\n---------------------------------------\n";

        // ===== Ereignisse nur für diesen Zyklus sammeln =====
        std::vector<std::string> events;

        if (warningMessage != previousWarning) {
            if (!warningMessage.empty()) {
                events.push_back("Neue Warnung: '" + warningMessage + "'");
            }
            else {
                events.push_back("Warnung quittiert");
            }
            previousWarning = warningMessage;
        }

        if (currentState != previousState) {
            events.push_back("Systemzustand geaendert zu '" + currentState + "'");
            previousState = currentState;
        }

        if (heaterState != previousHeaterState) {
            events.push_back(
                std::string("Heizung ")
                + (heaterState ? "eingeschaltet" : "ausgeschaltet"));
            previousHeaterState = heaterState;
        }

        if (buzzerState != previousBuzzerState) {
            events.push_back(
                std::string("Buzzer ")
                + (buzzerState ? "gestartet" : "gestoppt"));
            previousBuzzerState = buzzerState;
        }

        if (!events.empty()) {
            std::cout << "Ereignisse:\n";
            for (const auto& e : events) {
                std::cout << " - " << e << "\n";
            }
        }
        else {
            std::cout << "Ereignisse:\n - (keine Aenderungen in diesem Zyklus)\n";
        }

        //Simulierter Zyklusabstand
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // etwas warten, damit man das "Display" lesen kann
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}