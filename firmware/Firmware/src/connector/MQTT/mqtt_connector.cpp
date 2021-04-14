#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

/* on header as last one */
#include "mqtt_connector.h"

//#define mqtt_serial_debug

WiFiClient espClient;                       // WiFi ESP Client  
PubSubClient mqttclient(espClient);             // MQTT Client 
TaskHandle_t MQTTTaskHandle = NULL;

mqtt_msg_t msgpool[16];


QueueHandle_t msgpool_q=NULL;
QueueHandle_t new_msgpool_q=NULL;


mqtt_settings Settings;

void callback(char* topic, byte* payload, unsigned int length);
void MQTT_Connector_Task( void* prarm );

void MQTT_ConnectorStart( void ){
    msgpool_q = xQueueCreate( (sizeof(msgpool)/sizeof(msgpool[0]) ) , sizeof(&msgpool[0]) );
    if(msgpool_q==NULL){
        abort();
    }

    new_msgpool_q = xQueueCreate( (sizeof(msgpool)/sizeof(msgpool[0]) ) , sizeof(&msgpool[0]) );
    if(msgpool_q==NULL){
        abort();
    }


    for( uint32_t i=0; i< ( sizeof(msgpool) /sizeof(msgpool[0] ) )  ; i++) {
        xQueueSend(msgpool_q,&msgpool[i],0);
    }

/* This will created the MQTT task pinned to core 1 with prio 1 */
   xTaskCreatePinnedToCore(
   MQTT_Connector_Task,
   "MQTT_Task",
   10000,
   NULL,
   1,
   &MQTTTaskHandle,
   1);

}

void MQTT_Connector_Task( void* prarm ){
uint8_t ulNotificationValue=0x00;
#ifdef mqtt_serial_debug              
   Serial.println("MQTT_Connector_Task");
#endif
   mqttclient.setCallback(callback);             // define Callback function
   while(1==1){

   /* if settings have changed we need to inform this task that a reload and reconnect is requiered */ 
   if(Settings.enabled != false){
    ulNotificationValue = ulTaskNotifyTake( pdTRUE, 0 );
   } else {
    #ifdef mqtt_serial_debug
        Serial.println("MQTT disabled, going to sleep");
    #endif
    if(true == mqttclient.connected() ){
        mqttclient.disconnect();
    }
    ulNotificationValue = ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
    #ifdef mqtt_serial_debug
        Serial.println("MQTT awake from sleep");
    #endif
   }

   if( ulNotificationValue&0x01 != 0 ){
        #ifdef mqtt_serial_debug
            Serial.println("Reload MQTT Settings");
        #endif
      /* we need to reload the settings and do a reconnect */
      if(true == mqttclient.connected() ){
        mqttclient.disconnect();
      }
      //Settings = eepread_mqttsettings();
   }

   if(Settings.enabled != false ) {
  
       if(!mqttclient.connected()) {             
            /* sainity check */
            if( (Settings.port!=0) && (Settings.server[0]!=0) && ( Settings.enabled != false ) ){
                  /* We try only every second to connect */
                  #ifdef mqtt_serial_debug
                    Serial.print("Connecting to MQTT...");  // connect to MQTT
                  #endif
                  mqttclient.setServer(Settings.server, Settings.port); // Init MQTT     
                  if (mqttclient.connect(Settings.hostname, Settings.username, Settings.password)) {
                    #ifdef mqtt_serial_debug
                        Serial.println("connected");          // successfull connected  
                    #endif
                    mqttclient.subscribe(Settings.topic);             // subscibe MQTT Topic
                  } else {
                    #ifdef mqtt_serial_debug
                        Serial.println("failed");   // MQTT not connected       
                    #endif
                  }
            }
       } else{
            mqttclient.loop();                            // loop on client
            /* Check if we need to send data to the MQTT Topic, currently hardcode intervall */
           
              /* if we run in json mode we need to bulld the object */
              #ifdef mqtt_serial_debug
                Serial.println("Send JSON Payload");  
              #endif

            }
       }
       vTaskDelay( 100 / portTICK_PERIOD_MS );
   } 
 
}

void MQTT_Send_Message(uint32_t msglen, char* message){
    
    if(true==mqttclient.connected() ){
        // Now we can start to publish the message
        mqttclient.beginPublish(Settings.topic, msglen, false);
        mqttclient.write((uint8_t*)(message),msglen);
        // Now we're done!
        mqttclient.endPublish();
    }
    
}




/***************************
 * callback - MQTT message
 ***************************/
void callback(char* topic, byte* payload, unsigned int length) {
   mqtt_msg_t* q=NULL;
   xQueueReceive(msgpool_q,&q,0);
   if(q==NULL){
       return; //Out of space....
   }
   
   q->buffer = (uint8_t*)(malloc( length ));
   if(q->buffer==NULL){
       xQueueSend(msgpool_q,q,0 );
   }
   else{
       q->msglen = length;
   }
  
   if(pdTRUE != xQueueSend(new_msgpool_q,q,0)){
       MQTT_ReturnReceivedMessage(q);
   }

}

mqtt_msg_t* MQTT_GetReceivedMessageObj(){
   if(new_msgpool_q!=NULL){
    mqtt_msg_t* q=NULL;
    xQueueReceive(new_msgpool_q,&q,0);
    return q;
   } else {
       return NULL;
   }
}

void MQTT_ReturnReceivedMessage(mqtt_msg_t* q){
    if(new_msgpool_q!=NULL){
        if(q!=NULL){
            free(q->buffer);
            q->buffer=0;
            q->msglen=0;
            xQueueSend(msgpool_q,q,0 );
        }
    } else {
        //Not working Q not existing!
    }
}

mqtt_settings MQTT_GetSettings( void ){
    return Settings;
}

void MQTT_SetSettings(mqtt_settings settings){
    Settings = settings;
    if(MQTTTaskHandle!=NULL){
        xTaskNotify(MQTTTaskHandle, 0x01, eSetValueWithOverwrite );
    }
}

