#include "door.h"
#include "Arduino.h"
#include "constants.h"

int doorPosition = 2; // 0 = unknow; 1 = top; 2 = down
int doorIsMoving = 0; // 0 = stop; 1 = top; 2 = down
bool error = false;

dclass::dclass()
{
}

void dclass::SETUP()
{
  Serial.println("SETUP DOOR");
  pinMode(MOTOR_SPEED_CONTROL_PIN, OUTPUT);
  pinMode(MOTOR_DIRECTION_CONTROL_PIN, OUTPUT);
  pinMode(END_STOP_TOP, INPUT_PULLUP);
  pinMode(END_STOP_BOTTOM, INPUT_PULLUP);
}

void dclass::STOP()
{
  Serial.println("STOP DOOR");
  digitalWrite(MOTOR_SPEED_CONTROL_PIN, LOW);
  doorIsMoving = 0;
}

void dclass::OPEN()
{
  Serial.println('OPEN');

  if (!dclass::IS_MOVING() && doorPosition != 1)
  {
    doorIsMoving = 1;
    analogWrite(MOTOR_SPEED_CONTROL_PIN, 255);
    digitalWrite(MOTOR_DIRECTION_CONTROL_PIN, HIGH);
    long startTime = millis();
    while (dclass::IS_CLOSED())
    {

      if (digitalRead(END_STOP_TOP) == LOW)
      {
        Serial.println("Endstop top");
        dclass::STOP();
        doorPosition = 1;
        break;
      }
      
      dclass::FAILSAFE(startTime);
      delay(100);
    }
  }
}

void dclass::CLOSE()
{
  Serial.println('CLOSE');

  if (!dclass::IS_MOVING() && doorPosition != 2)
  {
    doorIsMoving = 2;
    analogWrite(MOTOR_SPEED_CONTROL_PIN, 255);
    digitalWrite(MOTOR_DIRECTION_CONTROL_PIN, LOW);
    long startTime = millis();
    while (dclass::IS_OPENED())
    {
      if (digitalRead(END_STOP_BOTTOM) == LOW)
      {
        Serial.println("Endstop bottom");
        dclass::STOP();
        doorPosition = 2;
        break;
      }
      dclass::FAILSAFE(startTime);

      delay(100);
    }
  }
}
void dclass::FAILSAFE(long startTime)
{
  long currentTime = millis();

  if (currentTime - startTime > MAX_ACTION_DURATION)
  {
    Serial.println("Auto break");
    dclass::STOP();
    doorPosition = 0; // inconnu
    error = true;
  }
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