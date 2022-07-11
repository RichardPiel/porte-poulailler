#include "buttons.h"
#include "Arduino.h"
#include "constants.h"
char msgs[5][15] = {
    "Right Key OK ",
    "Up Key OK    ",
    "Down Key OK  ",
    "Left Key OK  ",
    "Select Key OK"};
char start_msg[15] = {
    "Start loop "};
int adc_key_val[5] = {
    30, 150, 360, 535, 760};
int NUM_KEYS = 5;
int adc_key_in;
int key = -1;
int oldkey = -1;
bclass::bclass()
{
}
void bclass::SETUP()
{
    Serial.println("SETUP BUTTONS");
}

/**
 * @brief Convert ADC value to key number
 * 
 * @param input 
 * @return int 
 */
int bclass::GET_KEY(unsigned int input)
{
    int k;
    for (k = 0; k < NUM_KEYS; k++)
    {
        if (input < adc_key_val[k])
        {
            return k;
        }
    }
    if (k >= NUM_KEYS)
        k = -1; // No valid key pressed
    return k;
}

void bclass::LOOP()
{

    adc_key_in = analogRead(BUTTONS_PINS); // read the value from the sensor
    digitalWrite(13, HIGH);
    /* get the key */
    key = bclass::GET_KEY(adc_key_in); // convert into key press
    if (key != oldkey)
    {                               // if keypress is detected
        delay(50);                  // wait for debounce time
        adc_key_in = analogRead(BUTTONS_PINS); // read the value from the sensor
        key = bclass::GET_KEY(adc_key_in);  // convert into key press
        if (key != oldkey)
        {
            oldkey = key;
            if (key >= 0)
            {
                Serial.println(adc_key_in, DEC);
                Serial.println(msgs[key]);
            }
        }
    }
    digitalWrite(13, LOW);
}