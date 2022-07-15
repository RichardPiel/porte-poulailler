/**
 * @brief Stop le moteur après un laps de temps (en ms) pour
 * parer à une défaillance des endstops.
 * 
 */
#define MAX_ACTION_DURATION 30000

/** 
 * @brief Délai (en ms) avant d'ouvrir ou fermer la porte
 * après un changement de luminosité.
 * 
 */
#define INTERVAL_BEFORE_DO_SOMETHING 2000

/**
 * @brief Configuration des PINS pour le moteur, 
 * la photoresistance, les endstops, les boutons
 * 
 */
#define PHOTORESISTOR_PIN 0
#define MOTOR_SPEED_CONTROL_PIN 5
#define MOTOR_DIRECTION_CONTROL_PIN 4
#define MOTOR_SPEED 255
#define BUTTONS_PINS 7
#define END_STOP_TOP 7
#define END_STOP_BOTTOM 8

