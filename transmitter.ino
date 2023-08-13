#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <MFRC522.h>
#define echoPin 2
#define trigPin 3
#define dataPin 7  
#define temp_data 4
#define SS_PIN 10
#define RST_PIN 9
#define led 8
int ENA = A2,IN1 = A0,IN2 = A1,ENB = A3,IN3 = A4,IN4 = A5,distance,value=0,temp=0;
long duration=0;
OneWire oneWire(temp_data);
DallasTemperature sensors(&oneWire);
MFRC522 mfrc522(SS_PIN, RST_PIN);
int distance_func(){
  digitalWrite(trigPin, LOW);            
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;}
  float temperature(){
  sensors.requestTemperatures();           
  temp=sensors.getTempCByIndex(0);
  return temp;}
void setup(){
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(dataPin, INPUT);
  pinMode(led,OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW); 
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  sensors.begin();
  digitalWrite(led,HIGH);}
void loop() {
  analogWrite(ENA, 255),analogWrite(ENB, 255);
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    digitalWrite(led,HIGH);
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      uid += String(mfrc522.uid.uidByte[i], HEX);} 
    if(uid != 0 ){
      digitalWrite(led,LOW);
      analogWrite(ENA, 255);
        analogWrite(ENB, 255);
        digitalWrite(IN1, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN4, HIGH);
      for(;;){
        distance=distance_func();
        temp=temperature();
        value = digitalRead(dataPin);
        if(distance<10 || temp>38 || value==1 ){
          digitalWrite(led,HIGH);
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          if (temp>38){
            Serial.write(temp);
            exit(0);}
          if(value==1){
            Serial.write(value);
            exit(0);}}
        else{
          digitalWrite(led,LOW);
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);}}}
    else{
      digitalWrite(led,HIGH);}
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  exit(0);}}