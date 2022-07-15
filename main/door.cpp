#include "door.h"
#include "Arduino.h"
#include "constants.h"
#include "led.h"
#include "motor.h"

int doorPosition = 2; // 0 = unknow; 1 = top; 2 = down
int doorIsMoving = 0; // 0 = stop; 1 = top; 2 = down
bool error = false;

dclass::dclass()
{
}

void dclass::SETUP()
{
  Serial.println("SETUP DOOR");

  pinMode(END_STOP_TOP, INPUT_PULLUP);
  pinMode(END_STOP_BOTTOM, INPUT_PULLUP);
}

void dclass::STOP()
{
  Serial.println("STOP DOOR");
  motor.STOP();
  doorIsMoving = 0;
}

void dclass::OPEN()
{
  Serial.println('OPEN');

  if (!dclass::IS_MOVING() && doorPosition != 1)
  {
    doorIsMoving = 1;
    motor.UP();
    long startTime = millis();
    dclass::WAIT_FOR_OPENING(startTime);

    while (dclass::IS_CLOSED())
    {
      led.BLINK(500);

      if (digitalRead(END_STOP_TOP) == LOW)
      {
        Serial.println("Endstop top");
        motor.STOP();
        doorPosition = 1;
        led.START();

        break;
      }

      dclass::FAILSAFE(startTime);
      delay(250);
    }
  }
}

void dclass::CLOSE()
{
  Serial.println('CLOSE');

  if (!dclass::IS_MOVING() && doorPosition != 2)
  {
    doorIsMoving = 2;
    motor.DOWN();

    long startTime = millis();
    dclass::WAIT_FOR_CLOSENING(startTime);
    while (dclass::IS_OPENED())
    {
      led.BLINK(500);

      if (digitalRead(END_STOP_BOTTOM) == LOW)
      {
        Serial.println("Endstop bottom");
        motor.STOP();
        doorPosition = 2;
        led.STOP();
        break;
      }
      dclass::FAILSAFE(startTime);

      delay(250);
    }
  }
}
void dclass::FAILSAFE(long startTime)
{
  long currentTime = millis();

  if (currentTime - startTime > MAX_ACTION_DURATION)
  {
    Serial.println("Auto break");
    motor.STOP();
    doorPosition = 0; // inconnu
    error = true;
  }
}

/** @brief Permet de déterminer la position
 * initiale de la porte au démarrage
 */
void dclass::INITIALIZE()
{

  // La porte est en bas
  if (digitalRead(END_STOP_BOTTOM) == LOW)
  {
    Serial.println("Door is down");
    doorPosition = 2;
  }
  // La porte est en haut
  else if (digitalRead(END_STOP_TOP) == LOW)
  {
    Serial.println("Door is up");

    doorPosition = 1;
  }
  // La porte est en position inconnue
  else
  {
    doorPosition = 0;
    Serial.println("Door is unknown");
  }
}

void dclass::WAIT_FOR_OPENING(long startTime)
{
  while (digitalRead(END_STOP_BOTTOM) == LOW)
  {
    dclass::FAILSAFE(startTime);
    delay(100);
  }
  return;
}

void dclass::WAIT_FOR_CLOSENING(long startTime)
{
  while (digitalRead(END_STOP_TOP) == LOW)
  {
    dclass::FAILSAFE(startTime);
    delay(100);
  }
  return;
}

bool dclass::IS_MOVING()
{
  return doorIsMoving > 0;
}

bool dclass::IS_CLOSED()
{
  return doorPosition == 2;
}

bool dclass::IS_OPENED()
{
  return doorPosition == 1;
}
bool dclass::IS_ERROR()
{
  return error;
}

dclass door = dclass();