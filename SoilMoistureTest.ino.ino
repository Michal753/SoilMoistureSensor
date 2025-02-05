#include <SoilMoistureSensor.h>

// Dwa czujniki na pinach GPIO34 i GPIO35
SoilMoistureSensor soilSensors({34, 35}, 2071, 963, 60000); // Interwał 1 minuta; możesz zmienić interwał na 6 godzin (21600000 ms)
void setup() {
    Serial.begin(115200);
    soilSensors.begin();
}

void loop() {
    if (soilSensors.isReady()) {
        int moisture1 = soilSensors.read(0);
        int moisture2 = soilSensors.read(1);

        Serial.print("Czujnik 1: ");
        Serial.print(moisture1);
        Serial.println("%");

        Serial.print("Czujnik 2: ");
        Serial.print(moisture2);
        Serial.println("%");
    }

    delay(1000); // Sprawdzenie co sekundę
}