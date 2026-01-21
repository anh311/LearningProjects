#include "PIN.h"
#include <Arduino.h>

volatile bool pressFlag = false;    
unsigned long lastPressTime = 0;    
const unsigned long debounceDelay = 200; 

void IRAM_ATTR readSensor() {
    pressFlag = true; 
}

void setupInterrupts() {
    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON), readSensor, FALLING);
}

bool isButtonPressed() {
    if (pressFlag) {
        pressFlag = false; 

        unsigned long now = millis();
        if (now - lastPressTime > debounceDelay) {
            lastPressTime = now; 
            return true;         
        }
    }
    return false;
}
