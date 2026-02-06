#include <Arduino.h>
#include "PIN.h"
#include "INTERRUPT.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(DISPLAY_RS, DISPLAY_E, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

bool MODE = false;
bool lastMODE = false;
int rota_DEG=0;
ROTATION ROTA_STEPS;
bool rota_reset=false;
unsigned long lastPressTime_RESET = 0;   
unsigned long lastPressTime_ON_OFF= 0; 
const unsigned long debounceDelay = 200; 
int lastDeg = -1; 

void setup() {
  setupInterrupts();
  Serial.begin(9600);
  lcd.begin (16, 2);
  
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  pinMode(LEDRED, OUTPUT);  
  pinMode(LEDGREEN, OUTPUT);
  pinMode(LEDBLUE, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  lcd.clear(); 
  lcd.setCursor (0, 0);
  lcd.print("OFF MODE");

}

void loop() {

  if (digitalRead(BUTTON)== LOW){
    unsigned long now_ON_OFF = millis();
    if(now_ON_OFF - lastPressTime_ON_OFF > debounceDelay){
        lastPressTime_ON_OFF = now_ON_OFF;
        MODE=!MODE;     
    }
  }

  if (digitalRead(SW)==LOW){
    unsigned long now_RESET = millis();
    if (now_RESET - lastPressTime_RESET> debounceDelay){
      lastPressTime_RESET= now_RESET;
      rota_reset=true;
      }
  }
    
  
  if (MODE!=lastMODE){
    if (MODE){
      lcd.setCursor (0, 0);
      lcd.print("OFF MODE        ");
      lcd.setCursor (0, 1);
      lcd.print("              ");
      digitalWrite(LEDBLUE,LOW);
      digitalWrite(LEDGREEN,LOW);
      digitalWrite(LEDRED,HIGH);
    }
    lastMODE=MODE;
    lastDeg = -1;
  }
  if(!MODE){
      if(rota_reset){
        rota_DEG=0;
        reset_counter();
        rota_reset=false;
      }
      ROTA_STEPS=getROTA();
      rota_DEG=ROTA_STEPS.steps* 4.5;
      if (ROTA_STEPS.direction==1){
        digitalWrite(LEDBLUE,HIGH);
        digitalWrite(LEDGREEN,LOW);
        digitalWrite(LEDRED,LOW);
      }
      else if (ROTA_STEPS.direction==0){
        digitalWrite(LEDBLUE,LOW);
        digitalWrite(LEDGREEN,HIGH);
        digitalWrite(LEDRED,LOW);
      }
      
      if (rota_DEG != lastDeg) {
        lcd.setCursor (0, 0);
        lcd.print("GRAD:       ");
        lcd.setCursor (0, 1);
        lcd.print(rota_DEG);
        lcd.print("         ");
        lastDeg = rota_DEG;
      }
    }
}
