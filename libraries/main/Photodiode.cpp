#include <math.h>
#include "Printer.h"
extern Printer printer;

const int analogInputPin = A0; // Analog input pin

void setup() {
    Serial.begin(5000); // Wait time 5secs

    int res = 12;              // Voltage Resolution
    analogReadResolution(res); // for 12-bit resolution to track all minimal changes in voltage
    analogReadSpeed(ADC_HIGH_SPEED);
    float Vref = analogReference(EXTERNAL); // Reference voltage on AREF pin = 3V
}

void loop() {
    int sensorValue = analogRead(analogInputPin);
    float bits = pow(2, res) - 1;
    float voltage = sensorValue * (Vref / bits); // Assuming 12-bit ADC resolution
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");
    delay(1000);
}
