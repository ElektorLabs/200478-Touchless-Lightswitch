#ifndef __RELAIS_H__
    #define __RELAIS_H__

    #include <Arduino.h>

    class Relais{
        private:
        bool inverted = false;
        uint8_t pin=0;
        SemaphoreHandle_t Semampore=NULL;
        public:
        Relais( void );

        void begin(uint8_t pin);
        void begin(uint8_t pin, bool inverted);
        void begin(uint8_t pin, bool inverted, SemaphoreHandle_t sem);
        void on();
        void off();
        void SetStatus(bool sta);
        bool GetStatus(void );
        void RegisterSemaphore( SemaphoreHandle_t* SemPtr);
        void UnregisterSemaphore( void  );
        //We need to be able to register an kind of on change.....
    };

#endif