#include "InputHandler.h"

namespace ui {

InputHandler::InputHandler(int buttonPin)
    : buttonPin(buttonPin), buttonState(false) {}

bool InputHandler::readInput() {
    // In der Simulation wird der Tastenzustand bei jedem Aufruf umgeschaltet.
    buttonState = !buttonState;
    return buttonState;
}

bool InputHandler::isButtonPressed() const { return buttonState; }

} // namespace ui

