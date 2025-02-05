#ifndef SOILMOISTURESENSOR_H
#define SOILMOISTURESENSOR_H

#include <Arduino.h>
#include <vector>

class SoilMoistureSensor {
public:
    // Konstruktor obsługujący wiele czujników na różnych pinach
    SoilMoistureSensor(const std::vector<int>& pins, int dryValue = 2071, int wetValue = 963, unsigned long readInterval = 3600000);

    // Inicjalizacja czujników
    void begin();

    // Odczyt wilgotności dla konkretnego czujnika
    int read(int sensorIndex);

    // Sprawdzenie, czy minął czas na nowy pomiar
    bool isReady();

private:
    std::vector<int> _pins; // Lista pinów czujników
    int _dryValue;
    int _wetValue;
    unsigned long _readInterval;
    unsigned long _lastReadTime;

    // Funkcja do uśredniania odczytów
    int _averageReadings(int pin);
};

#endif