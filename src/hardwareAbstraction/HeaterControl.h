#pragma once

namespace hardware {

class HeaterControl {
public:
    explicit HeaterControl(int relayPin);

    void switchOn();
    void switchOff();
    bool getStatus() const;

private:
    int relayPin;
    bool isOn;
};

} // namespace hardware

