#pragma once

namespace hardware {
class HeaterControl;
}

namespace logic {

class SafetyManager {
public:
    SafetyManager();

    bool checkDryRun(int fillLevel, float tempRise);
    void emergencyShutdown(hardware::HeaterControl &heater);
    bool isDryRunDetected() const;

private:
    bool dryRunDetected;
};

} // namespace logic

