#ifndef interr
#define interr

struct ROTATION{
    int direction;
    int steps;
};

ROTATION getROTA();
bool readRESET_ROTA();
bool readON_OFF();
void setupInterrupts();
void reset_counter();
#endif