#include <Arduino.h>

//#define USR_HTTPS_SERVER

#ifndef USR_HTTPS_SERVER
    #include <WebServer.h>
#else 
    #include <ESPWebServer.hpp>
    #define WebServer ESPWebServer  
#endif


void SetupWebServer( ); // http version 
WebServer* WebserverGetHandle( void ); //Used to register new Functions to the Server
void WebserverLoopTask( void );
