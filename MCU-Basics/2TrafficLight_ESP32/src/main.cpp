#include <Arduino.h>
#include "PINS_H.h"

enum state{
  GREEN,
  YELLOW,
  RED,
  YELLOWRED

};

bool Ped = false;
state ampel1=GREEN;
state ampel2=RED;
unsigned long ampel1lastchange = 0;
unsigned long ampel2lastchange = 0;

const unsigned long debounceDelay = 100;
unsigned long lastDebounceTime = 0;
bool lastButtonState = HIGH;
bool ButtonState = HIGH;
unsigned long time1=0;
unsigned long lastPed=0;

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON,INPUT_PULLUP);
    pinMode(LEDFUSS,OUTPUT);
    pinMode(LEDFUSS1,OUTPUT);
    pinMode(LEDFUSS2,OUTPUT);
    pinMode(LED1RED,OUTPUT);
    pinMode(LED1YELLOW,OUTPUT);
    pinMode(LED1GREEN,OUTPUT);
    pinMode(LED2RED,OUTPUT);
    pinMode(LED2YELLOW,OUTPUT);
    pinMode(LED2GREEN,OUTPUT);
    pinMode(LED3RED,OUTPUT);
    pinMode(LED3YELLOW,OUTPUT);
    pinMode(LED3GREEN,OUTPUT);
}

void loop() {
  bool status=digitalRead(BUTTON);

  if(status!=lastButtonState){
    lastDebounceTime=millis();
  }

  if (millis()-lastDebounceTime>debounceDelay){
    if (status!=ButtonState){
      ButtonState=status;
      if(status==LOW && Ped==false){
        Ped=true;
        Serial.println("buttonpressed");
        digitalWrite(LEDFUSS1,HIGH);
      }
    }
  }
  lastButtonState=status;
  
  time1=millis();

  switch(ampel1){
    case GREEN:
      
      digitalWrite(LED1RED, LOW);
      digitalWrite(LED1YELLOW, LOW);
      digitalWrite(LED1GREEN, HIGH);
      digitalWrite(LED2RED, LOW);
      digitalWrite(LED2YELLOW, LOW);
      digitalWrite(LED2GREEN, HIGH);

      if (time1 - ampel1lastchange>10000){
        ampel1lastchange=time1;
        ampel2lastchange=time1;
        ampel1=YELLOW;
        ampel2=YELLOWRED;
      }
      if (Ped==true && (time1 - lastPed>3000)){
        ampel1lastchange=time1;
        ampel2lastchange=time1;
        ampel1=YELLOW;
        ampel2=YELLOWRED;
        lastPed=time1;
      }
      break;

    case YELLOW:
      
      digitalWrite(LED1RED, LOW);
      digitalWrite(LED1YELLOW, HIGH);
      digitalWrite(LED1GREEN, LOW);
      digitalWrite(LED2RED, LOW);
      digitalWrite(LED2YELLOW, HIGH);
      digitalWrite(LED2GREEN, LOW);

      if (time1 - ampel1lastchange>2000){
        ampel1lastchange=time1;
        ampel1=RED;
      }
      break;
    
    case RED:
      
      digitalWrite(LED1RED, HIGH);
      digitalWrite(LED1YELLOW, LOW);
      digitalWrite(LED1GREEN, LOW);
      digitalWrite(LED2RED, HIGH);
      digitalWrite(LED2YELLOW, LOW);
      digitalWrite(LED2GREEN, LOW);

      if (time1 - ampel1lastchange>10000){
        ampel1lastchange=time1;
        ampel1=YELLOWRED;
      }
      break;

    case YELLOWRED:
      
      digitalWrite(LED1RED, LOW);
      digitalWrite(LED1YELLOW, HIGH);
      digitalWrite(LED1GREEN, LOW);
      digitalWrite(LED2RED, LOW);
      digitalWrite(LED2YELLOW, HIGH);
      digitalWrite(LED2GREEN, LOW);

      if (time1 - ampel1lastchange>2000){
        ampel1lastchange=time1;
        ampel1=GREEN;
      }
      break;

  }
  switch(ampel2){
    case GREEN:
      digitalWrite(LEDFUSS, HIGH);
      digitalWrite(LEDFUSS1, LOW);
      digitalWrite(LED3RED, LOW);
      digitalWrite(LED3YELLOW, LOW);
      digitalWrite(LED3GREEN, HIGH);
      digitalWrite(LEDFUSS2, LOW);
      

      if (time1 - ampel2lastchange>10000){
        Ped=false;
        ampel2lastchange=time1;
        ampel2=YELLOW;
      }
      break;

    case YELLOW:
      digitalWrite(LEDFUSS, LOW);
      digitalWrite(LED3RED, LOW);
      digitalWrite(LED3YELLOW, HIGH);
      digitalWrite(LED3GREEN, LOW);
      digitalWrite(LEDFUSS2, HIGH);

      if (time1 - ampel2lastchange>2000){
        ampel2lastchange=time1;
        ampel2=RED;
        lastPed=time1;
      }
      break;
    
    case RED:
      
      digitalWrite(LED3RED, HIGH);
      digitalWrite(LED3YELLOW, LOW);
      digitalWrite(LED3GREEN, LOW);
      break;

    case YELLOWRED:
      
      digitalWrite(LED3RED, LOW);
      digitalWrite(LED3YELLOW, HIGH);
      digitalWrite(LED3GREEN, LOW);

      if (time1 - ampel2lastchange>2000){
        ampel2lastchange=time1;
        ampel2=GREEN;
      }
      break;
  }
}
