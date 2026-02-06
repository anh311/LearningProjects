#include <Arduino.h>
#include "PIN.h"
#include <DHT.h>

DHT dht(tempSensor, DHTTYPE);
int time1 =0;
int time2 =0;
float temp ;
float hum ;

void setup() {
  dht.begin();
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW); 
  setupInterrupts();
}

void loop() {

  if (millis() - time1 > 300000){
    time1 = millis();
    time2 = millis();
    digitalWrite(LED,HIGH);
    temp = dht.readTemperature();
    hum  = dht.readHumidity();
    Serial.print("Temp: "); Serial.println(temp);
    Serial.print("Humidity: "); Serial.println(hum);
  }

  if (isButtonPressed()) {
    time2 = millis();
    digitalWrite(LED,HIGH);
    Serial.println("BUTTON PRESSED!");
    temp = dht.readTemperature();
    hum  = dht.readHumidity();
    Serial.print("Temp: "); Serial.println(temp);
    Serial.print("Humidity: "); Serial.println(hum);
    }
  if (millis()-time2>10000) digitalWrite(LED,LOW);
}
