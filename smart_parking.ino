#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
const byte trig[]={2,4,6}, echo[]={3,5,7}, led[]={8,9,10};
const int THRESHOLD=12;
long distanceCm(byte t, byte e){
  digitalWrite(t,LOW); delayMicroseconds(2);
  digitalWrite(t,HIGH); delayMicroseconds(10); digitalWrite(t,LOW);
  long d=pulseIn(e,HIGH,30000); return d?d/58:999;
}
void setup(){
  for(int i=0;i<3;i++){pinMode(trig[i],OUTPUT);pinMode(echo[i],INPUT);pinMode(led[i],OUTPUT);}
  lcd.init(); lcd.backlight();
}
void loop(){
  int freeSlots=0; bool occupied[3];
  for(int i=0;i<3;i++){occupied[i]=distanceCm(trig[i],echo[i])<THRESHOLD;
    digitalWrite(led[i],occupied[i]); if(!occupied[i]) freeSlots++;}
  lcd.clear(); lcd.setCursor(0,0); lcd.print("Free: "); lcd.print(freeSlots);
  lcd.setCursor(0,1); lcd.print("1:");lcd.print(occupied[0]?"X":"O");
  lcd.print(" 2:");lcd.print(occupied[1]?"X":"O");
  lcd.print(" 3:");lcd.print(occupied[2]?"X":"O");
  delay(500);
}
