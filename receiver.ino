#include <SoftwareSerial.h>
SoftwareSerial gsmSerial(5,6),bluetooth(10, 11);
String data,longitude,latitude,altitude,link,message;
int receivedData=0;
void setup(){
  Serial.begin(9600);
  delay(1000);
  gsmSerial.begin(9600);
  delay(1000);
  bluetooth.begin(9600);
  delay(1000);}
void loop() {
  if (Serial.available() > 0) {
    if(bluetooth.available()) {
    data = bluetooth.readStringUntil(',');
    data = bluetooth.readStringUntil(',');
    longitude = bluetooth.readStringUntil(','); 
    Serial.print("longitude: ");
    Serial.println(longitude);
    latitude = bluetooth.readStringUntil(','); 
    Serial.print("latitude: ");
    Serial.println(latitude);
    altitude = bluetooth.readStringUntil(','); 
    Serial.print("altitude: ");
    Serial.println(altitude);
    data = bluetooth.readStringUntil(','); 
    data = bluetooth.readStringUntil(','); 
    data = bluetooth.readStringUntil(','); 
    data = bluetooth.readStringUntil(',');
    Serial.println ("Sending Message");
    gsmSerial.println("AT+CMGF=1");
    delay(1000);
    Serial.println ("Set SMS Number");   
    gsmSerial.println("AT+CMGS=\"+918943090727\"\r");
    delay(100);
    Serial.println ("Set SMS Content");
    link = "https://maps.google.com/maps?q=" + longitude + "," + latitude;
    message = "My current location: " + link;
    gsmSerial.println(message);
    Serial.println ("Finish");   
    gsmSerial.println((char)26);// ASCII code of CTRL+Z   
    delay(1000);}}}