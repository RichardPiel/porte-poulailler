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
    void INITIALIZE();
    bool IS_MOVING();
    bool IS_CLOSED();
    bool IS_OPENED();
    bool IS_ERROR();
    

private:
    void FAILSAFE(long startTime);
    void WAIT_FOR_OPENING(long startTime);
    void WAIT_FOR_CLOSENING(long startTime);
};

extern dclass door;

#endif
