#include <Preferences.h>
#include "datastore.h"

/* function prototypes */
void nvswrite_struct(void* data_in, uint32_t e_size, const char* key  );
bool nvsread_struct( void* element, uint32_t e_size, const char* key   );


/* This will be used as keys for the NVS */
#define WIFI_CONFIG_NAME "WIFICONF"
#define CREDENTIALS_NAME "CREDENTIALS"

Preferences prefs;
/**************************************************************************************************
 *    Function      : datastoresetup
 *    Description   : Gets the EEPROM Emulation set up
 *    Input         : none 
 *    Output        : none
 *    Remarks       : We use 4096 byte for EEPROM 
 **************************************************************************************************/
void datastoresetup() {
  prefs.begin("DATASTORE"); // use "DATASTORE" namespace
  read_wifi_config();
}

/**************************************************************************************************
 *    Function      : write_wifi_config
 *    Description   : writes the ntp config
 *    Input         : ntp_config_t c 
 *    Output        : none
 *    Remarks       : none 
 **************************************************************************************************/
void write_wifi_config(wifi_param_config_t c){
 nvswrite_struct( ( (void*)(&c) ), sizeof(wifi_param_config_t) , WIFI_CONFIG_NAME );    
}


/**************************************************************************************************
 *    Function      : read_wifi_config
 *    Description   : writes the ntp config
 *    Input         : none
 *    Output        : ntp_config_t
 *    Remarks       : none
 **************************************************************************************************/
wifi_param_config_t read_wifi_config( void ){
  wifi_param_config_t retval;
  if(false ==  nvsread_struct( (void*)(&retval), sizeof(wifi_param_config_t) , WIFI_CONFIG_NAME ) ){
    #ifdef DEBUG_SERIAL_DATASTORE
      Serial.println("Create blank WIFI Config");
    #endif
    bzero((void*)&retval,sizeof( wifi_param_config_t ));
    write_wifi_config(retval);
  } 
  return retval;
}

/**************************************************************************************************
 *    Function      : write_credentials
 *    Description   : writes the wifi credentials
 *    Input         : credentials_t
 *    Output        : none
 *    Remarks       : none
 **************************************************************************************************/
void write_credentials(credentials_t c){
   nvswrite_struct( ( (void*)(&c) ), sizeof(credentials_t) , CREDENTIALS_NAME );
}

/**************************************************************************************************
 *    Function      : read_credentials
 *    Description   : reads the wifi credentials
 *    Input         : none
 *    Output        : credentials_t
 *    Remarks       : none
 **************************************************************************************************/
credentials_t read_credentials( void ){
  credentials_t retval;
  if(false == nvsread_struct( (void*)(&retval), sizeof(credentials_t) , CREDENTIALS_NAME ) ){ 
    #ifdef DEBUG_SERIAL_DATASTORE
      Serial.println("Create blank WIFI Config");
    #endif
    bzero((void*)&retval,sizeof( credentials_t ));
    write_credentials(retval);
  }
  return retval;
}


/**************************************************************************************************
 *    Function      : nvsread_struct
 *    Description   : reads a given block from flash / eeprom 
 *    Input         : void* element, uint32_t e_size, uint32_t startaddr  
 *    Output        : bool ( true if read was okay )
 *    Remarks       : Reads a given datablock into flash and checks the the crc32 
 **************************************************************************************************/
bool nvsread_struct( void* element, uint32_t e_size, const char* key  ){
  bool done = false;
  if( e_size != prefs.getBytes(key, element, e_size) ){
    done = false;
  } else {
    done = true;
  }
  return done;
}

/**************************************************************************************************
 *    Function      : nvswrite_struct
 *    Description   : writes the display settings
 *    Input         : void* data, uint32_t e_size, uint32_t address 
 *    Output        : bool
 *    Remarks       : Writes a given datablock into flash and adds a crc32 
 **************************************************************************************************/
void nvswrite_struct(void* data_in, uint32_t e_size,const char* key ){
  uint32_t data_written = prefs.putBytes(key, data_in, e_size);
  if( e_size !=  data_written ){
    /* Write has failed ! */
    #ifdef DEBUG_SERIAL_DATASTORE
      Serial.printf("Write Error NVS, Bytes written %u, Bytes to write %u \n\r", data_written, e_size);
    #endif
  } else {
    /* Write done */
  }

}

/**************************************************************************************************
 *    Function      : datastore_erase
 *    Description   : writes the whole EEPROM with 0xFF  
 *    Input         : none
 *    Output        : none
 *    Remarks       : This will invalidate all user data 
 **************************************************************************************************/
void datastore_erase( void ){
  #ifdef DEBUG_SERIAL_DATASTORE
    Serial.printf("Erase Datastore");
  #endif
  prefs.clear();

}


