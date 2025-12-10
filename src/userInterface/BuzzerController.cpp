#include "BuzzerController.h"
    
namespace ui {

BuzzerController::BuzzerController(int buzzerPin)
    : buzzerPin(buzzerPin), playing(false), currentTone(ToneType::None) {}

void BuzzerController::playWarningTone() {
    playing = true;
    currentTone = ToneType::Warning;
}

void BuzzerController::playErrorTone() {
    playing = true;
    currentTone = ToneType::Error;
}

void BuzzerController::stopTone() {
    playing = false;
    currentTone = ToneType::None;
}

// Gibt den aktuellen Simulationszustand zurück.
bool BuzzerController::isPlaying() const { return playing; }

BuzzerController::ToneType BuzzerController::getCurrentTone() const {
    return currentTone;
}

std::string BuzzerController::getToneDescription() const {
    switch (currentTone) {
    case ToneType::Warning:
        return "Warning";
    case ToneType::Error:
        return "Error";
    default:
        return "None";
    }
}

} // namespace ui

