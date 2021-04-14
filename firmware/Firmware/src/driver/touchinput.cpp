#include <FunctionalInterrupt.h>
#include "touchinput.h"

/* We currently support only one MGC3x30 */
static uint8_t mgx3130_int_pin =0; 
static uint8_t mgx3130_rst_pin =0; 


#define DEBUGPRINT 

Flick flick;


void onTouchCb( FlickTouch_t touch, uint16_t period );
void airwheelCb(int32_t a);
void onGestureCb(FlickGesture_t gesture, FlickGestureClass_t gestClass, bool isEdgeFlick, bool inProgress);
void onXYZCb(uint16_t x, uint16_t y, uint16_t z);
void Touchinput_Task( void * pvParameters );

TaskHandle_t xHandle = NULL;


void TouchInput_begin( uint8_t xferPin, uint8_t resetPin ){
    //We setup a task for the touch input driver....
    mgx3130_int_pin =xferPin;
    mgx3130_rst_pin =resetPin;
    xTaskCreate( Touchinput_Task, "MGC3130Drv", 4096, NULL, tskIDLE_PRIORITY, &xHandle );
    configASSERT( xHandle );  
}

void Touchinput_init( void){
    #ifdef DEBUGPRINT
        Serial.println("Start MGC3130 driver...");
    #endif
    flick.begin(mgx3130_int_pin, mgx3130_rst_pin );
    flick.touchCallback = onTouchCb;
    flick.airWheelCallback = airwheelCb;
    flick.xyzCallback = onXYZCb;
    flick.gestureCallback = onGestureCb;
    delay(250);	//? Power up.....
    int ret = flick.SetRuntimeParameter(0xa1, 0x1f, 0xFFFFFFFF); // lock data output   <-----
    #ifdef DEBUGPRINT
        printf("ret: %d \n", ret);
    #endif
    ret = flick.SetRuntimeParameter(0x80, 0x1b, 0x1F); // disable calibration
    #ifdef DEBUGPRINT
        printf("ret: %d \n", ret);
    #endif
    
}

void Touchinput_Task( void* pvParameters ){

int poll_result=0;
    while(1==1){

        Touchinput_init();
        do{
                
                poll_result = flick.Poll();
                if(poll_result>=0){
                    delay(1);
                } else{
                    delay(10);
                }

        } while(poll_result>=-1);
    }
    //This should never been reached....
}


#ifdef DEBUGPRINT
    void onTouchCb( FlickTouch_t touch, uint16_t period ){
        switch (touch){ 
        case TOUCH_SOUTH_ELECTRODE:
                printf("TOUCH_SOUTH_ELECTRODE: %d, %d \n", touch, period);
            break;
        case TOUCH_WEST_ELECTRODE:
            
            printf("TOUCH_WEST_ELECTRODE: %d, %d \n", touch, period);
            break;
        case TOUCH_NORTH_ELECTRODE:
            printf("TOUCH_NORTH_ELECTRODE: %d, %d \n", touch, period);
            break;
        case TOUCH_EAST_ELECTRODE:
            printf("TOUCH_EAST_ELECTRODE: %d, %d \n", touch, period);
            break;
        case TOUCH_CENTER_ELECTRODE:
            printf("TOUCH_CENTER_ELECTRODE: %d, %d \n", touch, period);
            break;
        case TAP_SOUTH_ELECTRODE:
            printf("TAP_SOUTH_ELECTRODE: %d, %d \n", touch, period);
            break;
        case TAP_WEST_ELECTRODE:
            printf("TAP_WEST_ELECTRODE: %d, %d \n", touch, period);
            break;
        case TAP_NORTH_ELECTRODE:
            printf("TAP_NORTH_ELECTRODE: %d, %d \n", touch, period);
            break;
        case TAP_EAST_ELECTRODE:
            printf("TAP_EAST_ELECTRODE: %d, %d \n", touch, period);
            break;
        case TAP_CENTER_ELECTRODE:
            printf("TAP_CENTER_ELECTRODE: %d, %d \n", touch, period);
            break;
        case DOUBLE_TAP_SOUTH_ELECTRODE:
            printf("DOUBLE_TAP_SOUTH_ELECTRODE: %d, %d \n", touch, period);
            break;
        case DOUBLE_TAP_WEST_ELECTRODE:
            printf("DOUBLE_TAP_WEST_ELECTRODE: %d, %d \n", touch, period);
            break;
        case DOUBLE_TAP_NORTH_ELECTRODE:
            printf("DOUBLE_TAP_NORTH_ELECTRODE: %d, %d \n", touch, period);
            break;
        case DOUBLE_TAP_EAST_ELECTRODE:
            printf("DOUBLE_TAP_EAST_ELECTRODE: %d, %d \n", touch, period);
            break;
        case DOUBLE_TAP_CENTER_ELECTRODE:
            printf("DOUBLE_TAP_CENTER_ELECTRODE: %d, %d \n", touch, period);
            break;
        default:
            printf("Not defined touch: %d, %d \n", touch, period);
        }
    }
#else
    void onTouchCb( FlickTouch_t touch, uint16_t period ){
        switch (touch){ 
        case TOUCH_SOUTH_ELECTRODE:
         
            break;
        case TOUCH_WEST_ELECTRODE:
            
            break;
        case TOUCH_NORTH_ELECTRODE:
         
            break;
        case TOUCH_EAST_ELECTRODE:
         
            break;
        case TOUCH_CENTER_ELECTRODE:
         
            break;
        case TAP_SOUTH_ELECTRODE:
         
            break;
        case TAP_WEST_ELECTRODE:
         
            break;
        case TAP_NORTH_ELECTRODE:
         
            break;
        case TAP_EAST_ELECTRODE:
         
            break;
        case TAP_CENTER_ELECTRODE:
         
            break;
        case DOUBLE_TAP_SOUTH_ELECTRODE:
         
            break;
        case DOUBLE_TAP_WEST_ELECTRODE:
         
            break;
        case DOUBLE_TAP_NORTH_ELECTRODE:
         
            break;
        case DOUBLE_TAP_EAST_ELECTRODE:
         
            break;
        case DOUBLE_TAP_CENTER_ELECTRODE:
         
            break;
        default:

         break;
        }
    }

#endif

void airwheelCb(int32_t a) {
    #ifdef DEBUFPRINT
	    printf("Angle: %d \n", a);
    #endif
    
}

#ifdef DEBUGPRINT
void onGestureCb(FlickGesture_t gesture, FlickGestureClass_t gestClass, bool isEdgeFlick, bool inProgress){
	const char *g, *cl;
	switch (gesture){ 
	case GESTURE_GARBAGE_MODEL:
		g = "GARBAGE_MODEL";
		break;
	case FLICK_WEST_TO_EAST:
		g = "FLICK_WEST_TO_EAST";
		break;
	case FLICK_EAST_TO_WEST:
		g = "FLICK_EAST_TO_WEST";
		break;
	case FLICK_SOUTH_TO_NORTH:
		g = "FLICK_SOUTH_TO_NORTH";
		break;
	case FLICK_NORTH_TO_SOUTH:
		g = "FLICK_NORTH_TO_SOUTH";
		break;
	case CIRCLE_CLOCKWISE:
		g = "CIRCLE_CLOCKWISE";
		break;
	case CIRCLE_COUNTER_CLOCKWISE:
		g = "CIRCLE_COUNTER_CLOCKWISE";
		break;
	default:
		g = "NO_GESTURE";
	}
	
	switch (gestClass){ 
	case GESTURE_CLASS_GARBAGE_MODEL:
		cl = "GARBAGE_MODEL";
		break;
	case FLICK_GESTURE:
		cl = "FLICK_GESTURE";
		break;
	case CIRCULAR_GESTURE:
		cl = "CIRCULAR_GESTURE";
		break;
	default:
		cl = "UNKNOWN";
	}
	
	printf("Gesture: %s, class: %s, edge flick: %s, in progress: %s \n", g, cl, isEdgeFlick?"yes":"no", inProgress?"yes":"no" );
}
#else

void onGestureCb(FlickGesture_t gesture, FlickGestureClass_t gestClass, bool isEdgeFlick, bool inProgress){

	switch (gesture){ 
	case GESTURE_GARBAGE_MODEL:
	
		break;
	case FLICK_WEST_TO_EAST:
	
    	break;
	case FLICK_EAST_TO_WEST:
	
    	break;
	case FLICK_SOUTH_TO_NORTH:
        //Switch off
        Serial.println("Switch OFF");
    	break;
	case FLICK_NORTH_TO_SOUTH:
        //Switch on
        Serial.println("Switch ON");
    	break;
	case CIRCLE_CLOCKWISE:
	
    	break;
	case CIRCLE_COUNTER_CLOCKWISE:
	
    	break;
	default:

      break;
	}
	
	switch (gestClass){ 
	case GESTURE_CLASS_GARBAGE_MODEL:
	
    	break;
	case FLICK_GESTURE:
	
    	break;
	case CIRCULAR_GESTURE:
	
    	break;
	
    default:

        break;
	
    }
	
	
}
#endif

void onXYZCb(uint16_t x, uint16_t y, uint16_t z){
	#ifdef DEBUGPRINT
	    printf("x: %d, y: %d, z: %d \n", x, y, z);
	#endif
}

