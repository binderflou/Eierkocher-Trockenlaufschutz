#include "TemperatureSensor.h"

#include <utility>

#include "TimerService.h"

namespace hardware {

TemperatureSensor::TemperatureSensor(
    int tempPin, std::shared_ptr<TimerService> timerService)
    : tempPin(tempPin), temperature(20.0f), lastTemperature(20.0f),
      timerService(std::move(timerService)) {}

float TemperatureSensor::readTemperature() {
    // Temperatur nur aktualisieren, wenn seit der letzten Aktualisierung
    // mindestens 50 ms vergangen sind.
    if (timerService && timerService->elapsed(50)) {
        lastTemperature = temperature;
        
        // Ziel: in 3 Sekunden auf 100°C
        if (temperature < 100.0f) {
            temperature += 25.0f; // 80°C / 3 Schritte
            if (temperature > 100.0f) {
                temperature = 100.0f; // Clamp
            }
        }
        
        //temperature += 0.5f;
    }
    return temperature;
}

void TemperatureSensor::resetTemperature() {
    temperature = 20.0f;
    lastTemperature = 20.0f;
}

// Differenz zwischen aktuellem und letztem Temperaturwert
float TemperatureSensor::getDeltaT() const { return temperature - lastTemperature; }

} // namespace hardware
