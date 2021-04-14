#include <ArduinoJson.h>
#include "./../webserver_base.h"
#include "./../connector/MQTT/mqtt_connector.h"
#include "webapi_mqtt_connector.h"

//#define DEBUG_SERIAL_MQTT_CONNECTOR

void  WEBAPI_MQTT_ReadSettings();
void  WEBAPI_MQTT_WriteSettings();


void WEBAPI_MQTT_returnOK() {
    StaticJsonDocument<4096> doc;
    mqtt_settings Settings = MQTT_GetSettings();

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
            #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
                Serial.println("-------------------------------");
                Serial.println("JSON Keys found:");
                JsonObject documentRoot = doc.as<JsonObject>();
                for (JsonPair keyValue : documentRoot) {
                    Serial.println(keyValue.key().c_str());                   
                }
                Serial.println("-------------------------------");
            #endif
            
            if ( doc.containsKey("enabled")) {
                Settings.enabled = doc["enabled"];
                 #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
                    Serial.print("enabled:");
                    Serial.println(Settings.enabled);
                #endif 
            }

            if ( doc.containsKey("port")) {
                Settings.port = doc["port"];
                 #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
                    Serial.print("port:");
                    Serial.println(Settings.port);
                #endif  
            }

            {
                const char* data = doc["server"];
                if(data){
                strncpy( Settings.server, ( const char*)(data), sizeof(Settings.server));  
                #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
                    Serial.print("Server:");
                    Serial.println(Settings.server);
                #endif
                }
            }

            {
                const char* data = doc["hostname"];
                if(data){
                strncpy( Settings.hostname, ( const char*)(data), sizeof(Settings.hostname));
                #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
                    Serial.print("Server:");
                    Serial.println(Settings.hostname);
                #endif
                }
            }

            {
                const char* data = doc["topic"];
                if(data){
                strncpy( Settings.topic, ( const char*)(data), sizeof(Settings.topic));
                #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
                    Serial.print("topic:");
                    Serial.println(Settings.topic);
                #endif  
                }
            }

            {
                const char* data = doc["username"];
                if(data){
                strncpy( Settings.username, ( const char*)(data), sizeof(Settings.username));
                #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
                    Serial.print("username:");
                    Serial.println(Settings.username);
                #endif    
                }
            }

            {
                const char* data = doc["password"];
                if(data){
                strncpy( Settings.password, ( const char*)(data), sizeof(Settings.password));
                 #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
                    Serial.print("password:");
                    Serial.println(Settings.password);
                #endif      
                }
            }

            MQTT_SetSettings(Settings);
            
       
    }
    #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
        Serial.printf("Args: %i",server->args());        
        Serial.println("MQTT Send 200 OK");
    #endif
        server->send(200, "text/plain", "");

}

void WEBAPI_MQTT_RegisterConnector(){

        WebServer* server = WebserverGetHandle();
        if(server==NULL)
        {
            abort();
        }
        server->on("/mqtt/settings/settings.json",HTTP_GET, WEBAPI_MQTT_ReadSettings);
        server->on("/mqtt/settings/settings.json",HTTP_POST, WEBAPI_MQTT_returnOK , WEBAPI_MQTT_WriteSettings);

}

void  WEBAPI_MQTT_ReadSettings(){
    //We need to send a json with the current settings....
    mqtt_settings Settings = MQTT_GetSettings();
    StaticJsonDocument<192+(128*5)> doc;
    String output;

    doc["enabled"] = Settings.enabled;
    doc["server"] = Settings.server;
    doc["hostname"] = Settings.hostname;
    doc["port"] = Settings.port;
    doc["topic"] = Settings.topic;
    doc["username"] = Settings.username;
    doc["password"] = Settings.password;
    serializeJson(doc, output);
    
    #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
        Serial.println("----------------------------------------------");
        Serial.println("SEND MQTT CONNECTOR JSON:");
        Serial.println(output);
        Serial.println("----------------------------------------------");
    #endif

    WebServer* server = WebserverGetHandle();
    server->send(200,"application/json",output);


}

void  WEBAPI_MQTT_WriteSettings(){
    // char* input;
    // size_t inputLength; (optional)
    #ifdef DEBUG_SERIAL_MQTT_CONNECTOR
        Serial.println("----------------------------------------------");
        Serial.println("MQTT WRITE SETTINGS CONNECTOR");
        Serial.println("----------------------------------------------");
    #endif


    WebServer* server = WebserverGetHandle();
    HTTPUpload& upload  = server->upload();
    
    if (upload.status == UPLOAD_FILE_START) {
        
    } else if (upload.status == UPLOAD_FILE_WRITE) {
        
        
    } else if (upload.status == UPLOAD_FILE_END) {
        

        
    }



    

}
