#include <Arduino.h>
#include "connecting_to_wifi.cpp"
#include <PubSubClient.h>
/******************************************Some variables***********************************************/
const char* broker= "2934a0bd1369457cac14884fc9ea58f6.s2.eu.hivemq.cloud";//may be changed later if a better broker is discovered."
const char* mqtt_topic= "/************/signal"; //inside the topic its start with the broker username
const char* brokerUser= "************"; //broker user_name
const char* brokerPass= "************"; //broker pass
/*******************************************************************************************************/
WiFiClient espClient;
PubSubClient client(espClient);
/*****************************************functions*****************************************************/
/*Function used for reconnecting to the MQTT broker if the ESP32 is not connected.*/
void reconnect(){
    while(!client.connected()){
        Serial.print("\nconnecting to");
        Serial.println(broker);
        if(client.connect("esp32",brokerUser,brokerPass))/*esp32 is the client name*/{
            Serial.print("\nconnected to");
            Serial.println(broker);
            client.subscribe(mqtt_topic);
        }
        else {        
             Serial.print("\nTrying again..");
             delay(500);
        }

    }

}

/*Function used for recieving data from mqtt server and sending it to stm32 using uart*/
void callback(char* topic,byte* payload,unsigned int length){
    String message = "";
    for(int i=0; i<length; i++){
         message += (char)payload[i];
    }
    int receivedValue = message.toInt();
    Serial.print("Recieved value is: ");
    Serial.println(receivedValue);

    Serial1.println(receivedValue);////here sending data to STM32 using UART
}
