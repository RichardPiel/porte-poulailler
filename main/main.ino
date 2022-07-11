#include "door.h"
#include "buttons.h"
#include "photoresistor.h"
#include "led.h"
#include "Arduino.h"

unsigned long currentBrightnessDuration = 0;
unsigned int currentBrightness = 0;
const long intervalBeforeDoSomething = 2000; // 120 secondes

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
    return;
  }

  if (!door.IS_MOVING())
  {

    unsigned long currentMillis = millis();

    int reading = photoresistor.READ();

    switch (reading)
    {
    case pclass::BRIGHT:

      if (door.IS_CLOSED() == true)
      {
        if (currentBrightness != pclass::BRIGHT)
        {
          currentBrightnessDuration = currentMillis;
          break;
        }
        if (currentMillis - currentBrightnessDuration >= intervalBeforeDoSomething)
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
          currentBrightnessDuration = currentMillis;
          break;
        }
        if (currentMillis - currentBrightnessDuration >= intervalBeforeDoSomething)
        {
          door.CLOSE();
        }
      }
      break;
    }
    currentBrightness = reading;
  }
  delay(250);
}

void loadSetups()
{
  led.SETUP();
  photoresistor.SETUP();
  door.SETUP();
  buttons.SETUP();

  door.STOP();
}
