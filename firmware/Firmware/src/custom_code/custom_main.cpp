
#include <Arduino.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>

#include "./../webserver_base.h"
#include "./../wifi_net.h"
#include "./../version.h"

#include "./../driver/touchinput.h"
#include "./../driver/relais.h"
#include "./../connector/MQTT/mqtt_connector.h"
#include "./web_api/webapi_mqtt_connector.h"
#include "./web_api/webapi_switch.h"
#include "custom_config.h"


#define RELAIS_PIN_SET 4
#define RELAIS_PIN_RESET 15


SemaphoreHandle_t RelaisStateChangeSem=NULL;

Relais relais;


void LightswitchStatchange( bool newstate );

void  custom_setup(){
    //Custom setup 
    #ifdef custom_serial_debug
        Serial.println("Touchdriver Init");
    #endif
    TouchInput_begin(25,26);
    #ifdef custom_serial_debug
        Serial.println("Relais init");
    #endif
    RelaisStateChangeSem = xSemaphoreCreateBinary();
    relais.begin(RELAIS_PIN_SET,RELAIS_PIN_RESET,false,false,RelaisStateChangeSem);
    MQTT_ConnectorStart();
    WEBAPI_MQTT_RegisterConnector();
    WEBAPI_Switch_RegisterConnector(&relais);



}

void  custom_loop(){
    StaticJsonDocument<200> doc;
    //Custom loop
    mqtt_msg_t* msg=NULL;
    msg=MQTT_GetReceivedMessageObj();
    if(msg!=NULL){
        //We need to read the message and expect a JSON object....
        DeserializationError error = deserializeJson(doc, msg->buffer,msg->msglen);
          if (error) {
            #ifdef custom_serial_debug
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
            #endif
          } else {
              bool state = doc["state"];
              if( false == state){
                  relais.off();
              } else {
                  relais.on();
              }
          }
        
        MQTT_ReturnReceivedMessage(msg);
  
    }
    if(true==xSemaphoreTake(RelaisStateChangeSem,0)){
        //State has chaned....
        LightswitchStatchange(relais.GetStatus());

    }

}

void LightswitchStatchange( bool newstate ){
    String output;
    StaticJsonDocument<16> doc;
    doc["state"] = newstate ;
    serializeJson(doc, output);
    MQTT_Send_Message(output.length(),(char*)(output.c_str()));
}




