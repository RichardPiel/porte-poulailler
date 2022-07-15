#include "motor.h"
#include "constants.h"
#include "Arduino.h"
mclass::mclass()
{
}
void mclass::SETUP()
{
    Serial.println("SETUP MOTOR");
    pinMode(MOTOR_SPEED_CONTROL_PIN, OUTPUT);
    pinMode(MOTOR_DIRECTION_CONTROL_PIN, OUTPUT);
}

void mclass::STOP()
{
    digitalWrite(MOTOR_SPEED_CONTROL_PIN, LOW);
}

void mclass::DOWN()
{
    analogWrite(MOTOR_SPEED_CONTROL_PIN, MOTOR_SPEED);
    digitalWrite(MOTOR_DIRECTION_CONTROL_PIN, LOW);
}

void mclass::UP()
{
    analogWrite(MOTOR_SPEED_CONTROL_PIN, MOTOR_SPEED);
    digitalWrite(MOTOR_DIRECTION_CONTROL_PIN, HIGH);
}

mclass motor = mclass();
