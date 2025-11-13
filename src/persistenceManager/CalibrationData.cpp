#include "CalibrationData.h"

#include <utility>

namespace persistence {

CalibrationData::CalibrationData()
    : fillCalibValues{0, 25, 50, 75, 100}, tempCalibValues{20.0f, 40.0f, 60.0f, 80.0f, 100.0f} {}

const std::vector<int> &CalibrationData::getFillCalib() const { return fillCalibValues; }

const std::vector<float> &CalibrationData::getTempCalib() const { return tempCalibValues; }

void CalibrationData::setFillCalib(std::vector<int> values) {
    fillCalibValues = std::move(values);
}

void CalibrationData::setTempCalib(std::vector<float> values) {
    tempCalibValues = std::move(values);
}

} // namespace persistence

