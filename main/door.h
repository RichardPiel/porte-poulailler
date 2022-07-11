#ifndef door_h
#define door_h

class dclass
{
public:
    dclass();
    void SETUP();
    void STOP();
    void OPEN();
    void CLOSE();
    bool IS_MOVING();
    bool IS_CLOSED();
    bool IS_OPENED();
    bool IS_ERROR();

private:
    void FAILSAFE(long startTime);
};

extern dclass door;

#endif
