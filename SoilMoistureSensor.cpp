#include "SoilMoistureSensor.h"

// Konstruktor obsługujący wiele czujników
SoilMoistureSensor::SoilMoistureSensor(const std::vector<int>& pins, int dryValue, int wetValue, unsigned long readInterval)
    : _pins(pins), _dryValue(dryValue), _wetValue(wetValue), _readInterval(readInterval), _lastReadTime(0) {
}

// Inicjalizacja czujników
void SoilMoistureSensor::begin() {
    for (int pin : _pins) {
        pinMode(pin, INPUT);
    }
    _lastReadTime = millis();
}

// Sprawdzenie, czy minął czas na nowy pomiar
bool SoilMoistureSensor::isReady() {
    return millis() - _lastReadTime >= _readInterval;
}

// Odczyt wilgotności gleby dla konkretnego czujnika
int SoilMoistureSensor::read(int sensorIndex) {
    if (sensorIndex < 0 || sensorIndex >= _pins.size()) {
        return -1; // Nieprawidłowy indeks
    }

    if (!isReady()) {
        return -1; // Nie minął czas na nowy pomiar
    }

    _lastReadTime = millis(); // Aktualizacja czasu ostatniego pomiaru

    int averageReading = _averageReadings(_pins[sensorIndex]);

    // Mapowanie wartości na zakres 0-100%
    int moisture = map(averageReading, _dryValue, _wetValue, 0, 100);
    return constrain(moisture, 0, 100);
}

// Uśrednianie 20 odczytów co 5 sekund
int SoilMoistureSensor::_averageReadings(int pin) {
    const int numReadings = 20;
    int total = 0;

    for (int i = 0; i < numReadings; i++) {
        total += analogRead(pin);
        delay(5000); // Odczyt co 5 sekund
    }

    return total / numReadings;
}
