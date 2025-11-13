#pragma once

#include <string>

namespace logic {

class StateDetector {
public:
    StateDetector();

    std::string detectState(int fillLevel, float temperature);
    std::string getState() const;

private:
    std::string currentState;
};

} // namespace logic

