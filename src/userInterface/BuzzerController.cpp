#include "BuzzerController.h"

namespace ui {

BuzzerController::BuzzerController(int buzzerPin)
    : buzzerPin(buzzerPin), playing(false) {}

void BuzzerController::playWarningTone() { playing = true; }

void BuzzerController::playErrorTone() { playing = true; }

void BuzzerController::stopTone() { playing = false; }

bool BuzzerController::isPlaying() const { return playing; }

} // namespace ui

