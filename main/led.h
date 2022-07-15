#ifndef led_h
#define led_h
class lclass {
    public:
        lclass();
        void SETUP();
        void START();
        void STOP();
        void BLINK(long interval);
};

extern lclass led;

#endif