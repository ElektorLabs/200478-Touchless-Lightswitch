#include "relais.h"    

    Relais::Relais( void ){

    }

    void Relais::begin(uint8_t pin_set,uint8_t pin_reset){
        begin(pin_set,pin_reset,false,false);
    }

    void Relais::begin(uint8_t pin_set,uint8_t pin_reset, bool inverted_set, bool inverted_reset){
        begin(pin_set,pin_reset,inverted_set,inverted_reset,NULL);
    }

    void Relais::begin(uint8_t pin_set,uint8_t pin_reset, bool inverted_set,bool inverted_reset, SemaphoreHandle_t sem){
        this->inverted_set=inverted_set;
		this->inverted_reset=inverted_reset;
        this->pin_set=pin_set;
		this->pin_reset=pin_reset;
        this->Semampore=sem;
        pinMode(pin_set,OUTPUT);
		pinMode(pin_reset,OUTPUT);
		if(inverted_set){
				digitalWrite(pin_set,HIGH);
		} else {
				digitalWrite(pin_set,LOW);
		}
		
		if(inverted_reset){
				digitalWrite(pin_reset,HIGH);
		} else {
				digitalWrite(pin_reset,LOW);
		}
        off();
    }

    void Relais::on(){
        if(true==inverted){
			digitalWrite(pin_set,LOW);
			delay(750);
			digitalWrite(pin_set,HIGH);
			
        } else {
            digitalWrite(pin_set,HIGH);
			delay(750);
			digitalWrite(pin_set,LOW);            
        }
        if(this->Semampore!=NULL){
            xSemaphoreGive(this->Semampore);
        }
		this->status=true;

    }
    void Relais::off(){
	    if(false==inverted){
            digitalWrite(pin_reset,LOW);
			delay(750);
			digitalWrite(pin_reset,HIGH);
        } else {
			digitalWrite(pin_reset,HIGH);
			delay(750);
			digitalWrite(pin_reset,LOW);
        }
        if(this->Semampore!=NULL){
            xSemaphoreGive(this->Semampore);
        }
		this->status=false;
    }

    void Relais::SetStatus(bool sta){
        if(false==sta){
			off();
		} else {
			on();
		}
        if(this->Semampore!=NULL){
            xSemaphoreGive(this->Semampore);
        }
        
    }

    bool Relais::GetStatus(void ){
        return this->status;
    }

    void Relais::RegisterSemaphore( SemaphoreHandle_t* SemPtr){
        if(SemPtr!=NULL){
            this->Semampore=SemPtr;
        }
    }

    void Relais::UnregisterSemaphore(void  ){
            this->Semampore=NULL;
    }




