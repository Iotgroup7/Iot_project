#include "ThingSpeak.h"
#include <WiFi.h>
 
//-----------Wi-Fi Details---------//
char ssid[] = "505"; //SSID
char pass[] = "12345679"; // Password
//-------------------------------------------//
const int trigger = 18;
const int echo = 5;
long T;
int Status;
float distanceCM;
WiFiClient client;
unsigned long myChannelField = 1542072; // Channel ID
const int ChannelField1 = 1;// Which channel to write data
const int ChannelField2 = 2;
const char * myWriteAPIKey = "GCM8KYKWHQ3RFUH7"; // Your write API Key
 void setup()
{
 Serial.begin(115200);
 pinMode(trigger, OUTPUT);
 pinMode(echo, INPUT);
 WiFi.mode(WIFI_STA);
 ThingSpeak.begin(client);
}
void loop()
{
 if (WiFi.status() != WL_CONNECTED)
 {
 Serial.print("Attempting to connect to SSID: ");
 Serial.println(ssid);
 while (WiFi.status() != WL_CONNECTED)
 {
 WiFi.begin(ssid, pass);
 Serial.print(".");
delay(5000);
 }
 Serial.println("\nConnected.");
 }
 digitalWrite(trigger, LOW);
 delay(1);
 digitalWrite(trigger, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger, LOW);
 T = pulseIn(echo, HIGH);
 distanceCM = T * 0.034;
 distanceCM = distanceCM / 2;
 
 if(distanceCM<=10){
 Status=0;
 Serial.print("Distance in cm: ");
 Serial.println(distanceCM);
 Serial.println("parking sensor dirty");
 
 }
 else if(distanceCM>10 && distanceCM<=50){
 Status=1;
 Serial.print("Distance in cm: ");
 Serial.println(distanceCM);
 Serial.println("parking spot taken");
 
 }
 else {
 Status=2;
 Serial.print("Distance in cm: ");
 Serial.println(distanceCM);
 Serial.println("parking spot free");
 
 }
 ThingSpeak.writeField(myChannelField, ChannelField1,distanceCM, myWriteAPIKey);
 ThingSpeak.writeField(myChannelField,ChannelField2,Status,myWriteAPIKey);
 delay(100);
}
