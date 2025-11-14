#pragma once

#include <vector>

namespace persistence {

 /**
 * @brief Hält Kalibrierdaten für Füllstand und Temperatur.
 *
 * In einem echten System würden hier gemessene Referenzpunkte hinterlegt,
 * um Sensordaten zu linearisieren bzw. zu korrigieren.
 */

class CalibrationData {
public:
    CalibrationData();

    //liefert kalibierierten Füllwert in %
    const std::vector<int> &getFillCalib() const;

    //liefert kalibrierte Temperatur in °C
    const std::vector<float> &getTempCalib() const;

    //set Füllstand und Temperatur
    void setFillCalib(std::vector<int> values);
    void setTempCalib(std::vector<float> values);

private:
    //Kalibrierwerte
    std::vector<int> fillCalibValues;
    std::vector<float> tempCalibValues;
};

} // namespace persistence

