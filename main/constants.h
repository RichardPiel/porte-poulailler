/**
 * @file constants.h
 * @author Richard Piel <richard.piel@protonmail.com>
 * @version 0.1
 * @date 2022-07-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief Stop le moteur après un laps de temps (en ms) pour
 * parer à une défaillance des endstops.
 * 
 */
#define MAX_ACTION_DURATION 10000

/**
 * @brief Configuration des PINS pour le moteur, 
 * la photoresistance, les endstops, les boutons
 * 
 */
#define PHOTORESISTOR_PIN 0
#define MOTOR_SPEED_CONTROL_PIN 5
#define MOTOR_DIRECTION_CONTROL_PIN 4
#define BUTTONS_PINS 7
#define END_STOP_TOP 7
#define END_STOP_BOTTOM 8