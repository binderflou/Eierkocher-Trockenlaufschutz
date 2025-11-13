#pragma once

namespace ui {

class InputHandler {
public:
    explicit InputHandler(int buttonPin);

    bool readInput();
    bool isButtonPressed() const;

private:
    int buttonPin;
    bool buttonState;
};

} // namespace ui

