#ifndef photoresistor_h
#define photoresistor_h

class pclass
{

public:
    pclass();
    void SETUP();
    int READ();
    static const int BRIGHT = 0;
    static const int MEDIUM = 1;
    static const int DIM = 2;
    static const int DARK = 3;
};

extern pclass photoresistor;

#endif