#include "relais.h"    

    Relais::Relais( void ){

    }

    void Relais::begin(uint8_t pin){
        begin(pin,false);
    }

    void Relais::begin(uint8_t pin, bool inverted){
        begin(pin,inverted,NULL);
    }

    void Relais::begin(uint8_t pin, bool inverted, SemaphoreHandle_t sem){
        this->inverted=inverted;
        this->pin=pin;
        this->Semampore=sem;
        pinMode(pin,OUTPUT);
        off();
    }

    void Relais::on(){
        if(true==inverted){
            digitalWrite(pin,LOW);
        } else {
            digitalWrite(pin,HIGH);
        }
        if(this->Semampore!=NULL){
            xSemaphoreGive(this->Semampore);
        }

    }
    void Relais::off(){
        if(false==inverted){
            digitalWrite(pin,LOW);
        } else {
            digitalWrite(pin,HIGH);
        }
        if(this->Semampore!=NULL){
            xSemaphoreGive(this->Semampore);
        }
    }

    void Relais::SetStatus(bool sta){
        if(false==inverted){
            digitalWrite(pin,sta);
        } else {
            digitalWrite(pin,( !sta) );
        }
        if(this->Semampore!=NULL){
            xSemaphoreGive(this->Semampore);
        }
        
    }

    bool Relais::GetStatus(void ){
        bool stat = digitalRead(pin);
        if(true==inverted){
            stat=(!stat);
        } 
        return stat;
    }

    void Relais::RegisterSemaphore( SemaphoreHandle_t* SemPtr){
        if(SemPtr!=NULL){
            this->Semampore=SemPtr;
        }
    }

    void Relais::UnregisterSemaphore(void  ){
            this->Semampore=NULL;
    }




