#ifndef motor_h
#define motor_h

class mclass {
    public:
        mclass();
        void SETUP();
        void DOWN();
        void UP();
        void STOP();
};

extern mclass motor;

#endif