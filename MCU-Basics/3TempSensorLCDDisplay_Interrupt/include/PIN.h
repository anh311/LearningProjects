#define DHTTYPE DHT11
#ifndef PINS
#define PINS

const int BUTTON = 16;
const int LED = 17;
const int tempSensor= 4;
bool isButtonPressed();
void setupInterrupts(); 
extern volatile bool press;

#endif
