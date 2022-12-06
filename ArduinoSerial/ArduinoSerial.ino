#include <TimerOne.h>

int durum = 0;
int eskiZaman = 0;
int eskiZaman2 = 0;
int eskiZaman3 = 0;
int eskiZaman4 = 0;

int ledOn = 1000;
int ledOff = 500;
int port;

int ledOff1Second = 1000;
int echoTime = 0;
bool yap = true;
bool stopLedBool = false;
bool ledOnBool = false;

void setup() {
  Serial.begin(9600);
}

int veri = 0;

void loop() // BURADA VERİ OKUNUYOR INTERRUPT İLE KULLANMAK LAZIM
{
  noInterrupts();
  taskLed(ledOn, ledOff);
  interrupts();
  if(Serial.available()){
    serialPort();
  }
}

void serialPort(){
  
    if(Serial.find("stop")){
      stopLedBool = true;
      stopLed();
    }
    if(Serial.find("ledon=")){
      int a = Serial.parseInt(SKIP_ALL);
      ledOn = a;
    }
    if(Serial.find("ledoff=")){
      int b = Serial.parseInt(SKIP_ALL);
      ledOff = b;
    }
    if(Serial.find("changeport=")){
      int c = Serial.parseInt(SKIP_ALL);
      port = c;
      portChange(port);
    }
    if(Serial.available()>0){
      Serial.println(Serial.readString());
    }
}

void taskLed(int ledOn, int ledOff){ // LED YAKMA ve verileri geri gönderme

  if(ledOnBool && millis() - eskiZaman > ledOn){
    eskiZaman = millis();
    Serial.println("led Yandı");
    Serial.println(ledOn);
    ledOnBool = false;
  }
  if(!ledOnBool && millis() - eskiZaman > ledOff){
    eskiZaman = millis();
    Serial.println("led söndü");
    Serial.println(ledOff);
    ledOnBool = true;
  }
  if(millis() - eskiZaman2 > echoTime){
    eskiZaman2 = millis();
    if(Serial.available()){
    }
  }
}

void stopLed(){
  while(stopLedBool){
    if(millis() - eskiZaman4 > ledOff1Second){
      eskiZaman4 = millis();
      Serial.println("stop ledi yandı");
    }
    if(millis() - eskiZaman3 > 10){
      eskiZaman3 = millis();
      if(Serial.available() && Serial.find("start")){
        Serial.println("start ledi yandı");
        stopLedBool = false;
      }
    }
  }
}

void portChange(int port){  // PORT DEĞİŞTİRME
  if(yap){
    Serial.println(port);
    Serial.end();
    Serial.begin(port);
    yap = !yap;
  }
}
