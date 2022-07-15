#include "led.h"
#include "Arduino.h"

unsigned long previousMillis = 0; 
int ledState = LOW;

lclass::lclass()
{
}

void lclass::SETUP()
{
  Serial.println("SETUP LEP");
  pinMode(LED_BUILTIN, OUTPUT);
}

void lclass::BLINK(long interval)
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    if (ledState == LOW)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }

    digitalWrite(LED_BUILTIN, ledState);
  }
}

void lclass::START()
{
    digitalWrite(LED_BUILTIN, HIGH);
}

void lclass::STOP()
{
    digitalWrite(LED_BUILTIN, LOW);
}

lclass led = lclass();