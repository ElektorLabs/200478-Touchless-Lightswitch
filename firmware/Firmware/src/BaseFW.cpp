//****************************************************************************
// Firmware Base Version 0.1 - 06.04.2021
//
//****************************************************************************
#include <Arduino.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "FS.h"
#include <Wire.h> 
#include "SPIFFS.h"
#include <Update.h>


#include "./wifi_net.h"
#include "./datastore.h"
#include "config.h"

#if __has_include("./custom_code/custom_main.h") 
  #include "./custom_code/custom_main.h"
#endif




/**************************************************************************************************
 *    Function      : setup_iopins
 *    Description   : This will enable the IO-Pins
 *    Input         : none 
 *    Output        : none
 *    Remarks       : none 
 **************************************************************************************************/
void setup_iopins( void ){
  
  pinMode(0,INPUT_PULLUP); //Boot Pin 
 
}


/**************************************************************************************************
 *    Function      : StartOTA
 *    Description   : This will prepare the OTA Service
 *    Input         : none 
 *    Output        : none
 *    Remarks       : none 
 **************************************************************************************************/
void StartOTA(){

#ifdef DEBUG_SERIAL_OTA
  Serial.println("Start OTA Service");
#endif
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      #ifdef DEBUG_SERIAL_OTA
        Serial.println("Start updating " + type);
      #endif
    })
    .onEnd([]() {
      #ifdef DEBUG_SERIAL_OTA
        Serial.println("\nEnd");
      #endif
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      #ifdef DEBUG_SERIAL_OTA
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      #endif
    })
    .onError([](ota_error_t error) {
      #ifdef DEBUG_SERIAL_OTA
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
      #endif
    });

  ArduinoOTA.begin();

}


void  __attribute__((weak)) custom_setup(){

}

void  __attribute__((weak))custom_loop(){

}

/**************************************************************************************************
 *    Function      : setup
 *    Description   : This will onyl run once after boot
 *    Input         : none 
 *    Output        : none
 *    Remarks       : none 
 **************************************************************************************************/
void setup() {
  Serial.begin(115200);
  SPIFFS.begin(); /* This can be called multiple times, allready mounted it will just return */
  datastoresetup();
  
  setup_iopins();

  //We also need to mount the SPIFFS
  if(!SPIFFS.begin(true)){
     #ifdef DEBUG_SERIAL
      Serial.println("An Error has occurred while mounting SPIFFS");
     #endif
  }
  //Next step is to setup wifi and check if the configured AP is in range
  WiFiClientEnable(true); //Force WiFi on 
  WiFiForceAP(false); //Diable Force AP
  #ifdef DEBUG_SERIAL
    Serial.println("Continue boot");
  #endif
  

  RegisterWiFiConnectedCB(StartOTA);
  #ifdef DEBUG_SERIAL
    Serial.println("Initialize WiFi");
  #endif
 //If the button is pressed during start we will go to the AP Mode
    if(0 != digitalRead(0) ){
      initWiFi( false, false );
    } else {
      #ifdef DEBUG_SERIAL
        Serial.println("Force System to AP");
      #endif
      initWiFi( false , true );   
    }
  custom_setup();
}


/**************************************************************************************************
 *    Function      : loop
 *    Description   : Main Loop
 *    Input         : none 
 *    Output        : none
 *    Remarks       : none 
 **************************************************************************************************/
void loop() {
  /* This will be executed in the arduino main loop */
  ArduinoOTA.handle();
  NetworkLoopTask();
  custom_loop();
}


