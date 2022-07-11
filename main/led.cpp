#include "led.h"
#include "Arduino.h"

lclass::lclass()
{
}

void lclass::SETUP()
{
  Serial.println("SETUP LEP");
  pinMode(LED_BUILTIN, OUTPUT);
}

void lclass::BLINK()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

lclass led = lclass();