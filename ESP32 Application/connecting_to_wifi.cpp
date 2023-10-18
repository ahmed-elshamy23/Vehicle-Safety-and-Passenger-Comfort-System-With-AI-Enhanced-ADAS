#include <Arduino.h>
#include <WiFi.h>

const char* ssid= "WE_CEAF20";
const char* pass= "95599899";
/*Function used for connecting to the WiFi*/
void setupWiFi(){
     delay(100);
     Serial.print("\nConnecting to ");
     Serial.println(ssid);

     WiFi.begin(ssid,pass);
     while(WiFi.status() != WL_CONNECTED){
        delay(100);
        Serial.print("-");
     }

     Serial.print("\nConnected to");
     Serial.println(ssid);
}