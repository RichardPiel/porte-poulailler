#include "door.h"
#include "buttons.h"
#include "photoresistor.h"
#include "led.h"
#include "Arduino.h"
#include "constants.h"

unsigned long currentBrightnessDuration = 0;
unsigned int currentBrightness = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("SETUP");
  loadSetups();
}

void loop()
{

  if (door.IS_ERROR())
  {
    Serial.println("ERROR");
    led.BLINK(250);
    return;
  }

  if (!door.IS_MOVING())
  {

    unsigned long currentMillis = millis();

    int reading = photoresistor.READ();
    Serial.print("analogRead reading: ");
    Serial.println(reading);
    switch (reading)
    {
    case pclass::MEDIUM:

      if (door.IS_CLOSED() == true)
      {
        if (currentBrightness != pclass::MEDIUM)
        {
          currentBrightness = reading;
          currentBrightnessDuration = currentMillis;
          break;
        }
        if (currentMillis - currentBrightnessDuration >= INTERVAL_BEFORE_DO_SOMETHING)
        {
          door.OPEN();
        }
      }
      break;
    case pclass::DARK:
      if (door.IS_OPENED())
      {
        if (currentBrightness != pclass::DARK)
        {
          currentBrightness = reading;
          currentBrightnessDuration = currentMillis;
          break;
        }
        if (currentMillis - currentBrightnessDuration >= INTERVAL_BEFORE_DO_SOMETHING)
        {
          door.CLOSE();
        }
      }
      break;
    }
  }
  delay(125);
}

void loadSetups()
{
  led.SETUP();
  photoresistor.SETUP();
  door.SETUP();
  buttons.SETUP();

  door.INITIALIZE();
}
