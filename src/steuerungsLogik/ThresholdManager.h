#pragma once

namespace logic {

class ThresholdManager {
public:
    ThresholdManager();

    void setWarningThreshold(int value);
    int getWarningThreshold() const;

    void setCriticalThreshold(int value);
    int getCriticalThreshold() const;

private:
    int warningThreshold;
    int criticalThreshold;
};

} // namespace logic

