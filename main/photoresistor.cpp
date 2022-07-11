#include "photoresistor.h"
#include "Arduino.h"
#include "constants.h"

const int sensorMin = 400;
const int sensorMax = 1000;

const int BRIGHT = 0;
const int MEDIUM = 1;
const int DIM = 2;
const int DARK = 3;

pclass::pclass()
{
}

void pclass::SETUP()
{
  Serial.println("SETUP PHOTORESISTOR");

}
int pclass::READ()
{
    int sensorReading = analogRead(PHOTORESISTOR_PIN);
    //     Serial.print("analogRead currentBrightness: ");
    // Serial.println(sensorReading);
    return map(sensorReading, sensorMin, sensorMax, 0, 3);
}

pclass photoresistor = pclass();