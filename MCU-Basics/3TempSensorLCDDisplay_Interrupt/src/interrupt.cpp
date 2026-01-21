#include "PIN.h"
#include <Arduino.h>

volatile bool press = false;

void IRAM_ATTR readSensor(){
    static uint32_t lastTime = 0;
    uint32_t now = micros();  // genau, schnelle Zeit

    if (now - lastTime > 200000) { // 200 ms Debounce
        press = true;             // Event setzen
        lastTime = now;           // Zeit merken
    }

}

void setupInterrupts() {
    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON), readSensor, FALLING);
}

bool isButtonPressed() {
     if (press) {
        press = false;            
        return true;
    }
    return false;
}
