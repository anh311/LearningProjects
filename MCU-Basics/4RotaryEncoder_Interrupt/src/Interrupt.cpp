#include "PIN.h"
#include "INTERRUPT.h"
#include <Arduino.h>

volatile long ROTATION_SIGNAL=0;
volatile int last_counter=0;
volatile int ENCODER_DIRECTION = 2;
volatile int lastEncoded = 0;

void SIGNAL_AB() {
  int MSB = (PIND & (1 << 2)) >> 2;
  int LSB = (PIND & (1 << 3)) >> 3; 
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  switch(sum) {
    // Vorwärts
    case 0b0001:
    case 0b0111:
    case 0b1110:
    case 0b1000:
      ROTATION_SIGNAL++;
      ENCODER_DIRECTION=1;
      break;
    // Rückwärts
    case 0b0010:
    case 0b0100:
    case 0b1101:
    case 0b1011:
      ROTATION_SIGNAL--;
      ENCODER_DIRECTION=0;
      break;
  }

  lastEncoded = encoded;
}

void setupInterrupts() {
    int MSB = digitalRead(ENCODER_A);
    int LSB = digitalRead(ENCODER_B);
    lastEncoded = (MSB << 1) | LSB;
    pinMode(ENCODER_A, INPUT_PULLUP);
    pinMode(ENCODER_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_B), SIGNAL_AB, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A), SIGNAL_AB,CHANGE);
}

ROTATION getROTA(){
    
    ROTATION result ={0,0};
    noInterrupts();
    result.direction=ENCODER_DIRECTION;
    last_counter= ROTATION_SIGNAL;
    result.steps=ROTATION_SIGNAL;
    interrupts();  
    return result;
}
void reset_counter(){
    noInterrupts();
    last_counter=0;
    ROTATION_SIGNAL=0;
    interrupts();
}