//#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "your_ssid";
const char* pass = "your_password";

const char* brokerUser= "**************";
const char* brokerPass= "**************";
const char* broker= "mqttx_22895b4e";
const char* outTopic= "new/signal";


WiFiClient espClient;
PubSubClient client(espClient);

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


void reconnect(){
    while(!client.connected()){
        Serial.print("\nconnecting to");
        Serial.println(broker);
        if(client.connect("esp32",brokerUser,brokerPass))/*esp32 is the client name*/{
            Serial.print("\nconnected to");
            Serial.println(broker);
            client.subscribe(outTopic);
        }
        else {        
             Serial.print("\nTrying again..");
             delay(500);
        }

    }

}
