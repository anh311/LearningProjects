#include <Arduino.h>
const int BUT = 16;
const int LEDPIN1 = 17;
const unsigned long debounceDelay = 1000;

/* //In this version, the button press is registered multiple times if the button is held down continuously!

unsigned long lastPressTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUT,INPUT_PULLUP);
  pinMode(LEDPIN1,OUTPUT);
}

void loop() {
  bool button=digitalRead(BUT);
  unsigned long curTime=millis();
  if( button==LOW && (curTime-lastPressTime)>debounceDelay){
        Serial.println("buttonpressed");
        lastPressTime=curTime;
        digitalWrite(LEDPIN1, !digitalRead(LEDPIN1));
  }
}
*/

//A new button press will only be registered after at least one debounceDelay has passed since the previous press.
unsigned long lastDebounceTime = 0;
bool lastButtonState = HIGH;
bool buttonState = HIGH;
bool LEDstatus = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(BUT,INPUT_PULLUP);
  pinMode(LEDPIN1,OUTPUT);
}

void loop() {
  bool button=digitalRead(BUT);
  if(button != lastButtonState){
    lastDebounceTime=millis();
  }

  if((millis()-lastDebounceTime)>debounceDelay){
    if(button != buttonState){
      buttonState=button;
      if(buttonState==LOW){
        Serial.println("buttonpressed");
        digitalWrite(LEDPIN1, !digitalRead(LEDPIN1));
      }
    }

  }
  lastButtonState=button;
}


