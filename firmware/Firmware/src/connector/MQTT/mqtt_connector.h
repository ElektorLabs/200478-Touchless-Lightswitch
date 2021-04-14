#ifndef __MQTTT_CONNECTOR_H__
 #define __MQTTT_CONNECTOR_H__

typedef struct {
    uint8_t *buffer;
    uint8_t msglen;
} mqtt_msg_t;

typedef struct settings{
    bool enabled;
    char server[128];
    char hostname[128];
    uint16_t port;
    char topic[128];
    char username[128];
    char password[128];
}mqtt_settings;

void MQTT_ConnectorStart( void ) ;
void MQTT_Send_Message( uint32_t msglen, char* message);
mqtt_msg_t* MQTT_GetReceivedMessageObj();
void MQTT_ReturnReceivedMessage(mqtt_msg_t* q);
mqtt_settings MQTT_GetSettings( void );
void MQTT_SetSettings(mqtt_settings settings);




#endif