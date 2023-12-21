#include <Servo.h>
#include <Ultrasonic.h>
#include <SPI.h>
#include <MFRC522.h>
#include "rgb_lcd.h"

#define RST_PIN 9
#define SS_PIN 10
MFRC522 module_rfid(SS_PIN, RST_PIN);
rgb_lcd lcd;


float distance, duration;
int ledr = 7;
int ledg = 6;
int servo = 5;
Ultrasonic ultrasonic(3,4); // Trig et Echo
Servo servo_5;


void setup()
{
  lcd.begin(16, 2);
  lcd.setRGB(255,255,255);
  Serial.begin(9600);
  servo_5.attach(8);
  servo_5.write(0);
  SPI.begin();
  module_rfid.PCD_Init();
  lcd.print("Bienvenu ISAMM");
  digitalWrite(ledr,HIGH);
}

void loop()
{
  delay(500);
  delay(100);
 
  distance= ultrasonic.read();
  if(distance<70){
    lcd.clear();
    lcd.print("Scannez votre");
    lcd.setCursor(0, 1);
    lcd.print("carte ou badge..");   
  if ( ! module_rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! module_rfid.PICC_ReadCardSerial()) 
  {
    return;
  }
   String UID = "";

  for (byte i = 0; i < module_rfid.uid.size; i++) {
    UID.concat(String(module_rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    UID.concat(String(module_rfid.uid.uidByte[i], HEX));
  }

  UID.toUpperCase();
  if (UID.substring(1) == "E6 3A 5F AF" ) {
    digitalWrite(ledr, LOW);
    delay(500);
    digitalWrite(ledg, HIGH);
    delay(500);
    servo_5.write(90);
    lcd.clear();
    lcd.print("welcome");
    lcd.setCursor(0, 1);
    lcd.print("Nada Bouhadida"); 
    delay(2500);
    
  } else {
    digitalWrite(ledr, HIGH);
    digitalWrite(ledg, LOW);
    lcd.clear();
    lcd.print("unkown");
    delay(1500);
    servo_5.write(0);
  }


  }
  else{
    lcd.clear();
    lcd.print("Bienvenu ISAMM");
    digitalWrite(ledr, HIGH);
    digitalWrite(ledg, LOW);
  
    servo_5.write(0);
  }
  
  Serial.print("Distance : ");
  Serial.println(distance);
  delay(100);
  
}