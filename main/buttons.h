#ifndef buttons_h
#define buttons_h

class bclass
{
public:
    bclass();
    void SETUP();
    void LOOP();
private:
    int GET_KEY(unsigned int input);

};

extern bclass buttons;

#endif
