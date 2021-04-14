#include <ArduinoJson.h>
#include "./../webserver_base.h"
#include "./../connector/MQTT/mqtt_connector.h"

#include "webapi_switch.h"

#define DEBUG_SERIAL_SWITCH


Relais* rel_obj=NULL;

void WEBAPI_Switch_ReadSettings( void );
void WEBAPI_Switch_WriteSettings( void );



void WEBAPI_Switch_returnOK() {
    StaticJsonDocument<512> doc;
    WebServer* server = WebserverGetHandle();
    if(server->args()==1){
        //We only expect one argument here....
            String data = server->arg(0);
            Serial.println(data);
            
            DeserializationError error = deserializeJson(doc, data);
            if (error) {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
                return;
            }
            #ifdef DEBUG_SERIAL_SWITCH
                Serial.println("-------------------------------");
                Serial.println("JSON Keys found:");
                JsonObject documentRoot = doc.as<JsonObject>();
                for (JsonPair keyValue : documentRoot) {
                    Serial.println(keyValue.key().c_str());                   
                }
                Serial.println("-------------------------------");
            #endif
            
            if ( doc.containsKey("status")) {
                bool enabled = doc["status"];
                 #ifdef DEBUG_SERIAL_SWITCH
                    Serial.print("staus:");
                    Serial.println(enabled);
                #endif 
                if(rel_obj!=NULL){
                    rel_obj->SetStatus(enabled);
                }
            }
           //Set output....
            
       
    }
    #ifdef DEBUG_SERIAL_SWITCH
        Serial.printf("Args: %i",server->args());        
        Serial.println("SWITCH Send 200 OK");
    #endif
        server->send(200, "text/plain", "");
}

void WEBAPI_Switch_RegisterConnector(Relais* robj){

    rel_obj=robj;
    WebServer* server = WebserverGetHandle();
    if(server==NULL)
    {
        abort();
    }
    server->on("/switch/settings/settings.json",HTTP_GET, WEBAPI_Switch_ReadSettings);
    server->on("/switch/settings/settings.json",HTTP_POST, []() { WEBAPI_Switch_returnOK(); }, WEBAPI_Switch_WriteSettings);

 }

void WEBAPI_Switch_ReadSettings( void ){
    //We need to send a json with the current settings....
    StaticJsonDocument<192+(128*5)> doc;
    String output;
    if(rel_obj!=NULL){
         doc["status"] =(bool)(rel_obj->GetStatus());
    } else {
        doc["status"] = (bool)(false);
    }
    
    serializeJson(doc, output);
    WebServer* server = WebserverGetHandle();
    #ifdef DEBUG_SERIAL_SWITCH
        Serial.println("----------------------------------------------");
        Serial.println("SEND SWITCH JSON:");
        Serial.println(output);
        Serial.println("----------------------------------------------");
    #endif
    server->send(200,"application/json",output);


}

void WEBAPI_Switch_WriteSettings( void ){

    WebServer* server = WebserverGetHandle();
    HTTPUpload& upload  = server->upload();
    
    if (upload.status == UPLOAD_FILE_START) {
        //Check if we have a buffer with enough size in it....            
        
    } else if (upload.status == UPLOAD_FILE_WRITE) {
        //Add the current data to our buffer....
       
        
        
    } else if (upload.status == UPLOAD_FILE_END) {
        
    }


}