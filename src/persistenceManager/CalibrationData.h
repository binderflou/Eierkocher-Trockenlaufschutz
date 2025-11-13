#pragma once

#include <vector>

namespace persistence {

class CalibrationData {
public:
    CalibrationData();

    const std::vector<int> &getFillCalib() const;
    const std::vector<float> &getTempCalib() const;

    void setFillCalib(std::vector<int> values);
    void setTempCalib(std::vector<float> values);

private:
    std::vector<int> fillCalibValues;
    std::vector<float> tempCalibValues;
};

} // namespace persistence

