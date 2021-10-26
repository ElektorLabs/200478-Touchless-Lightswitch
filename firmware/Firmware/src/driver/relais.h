#ifndef __RELAIS_H__
    #define __RELAIS_H__

    #include <Arduino.h>

    class Relais{
        private:
        bool inverted_set = false;
		bool inverted_reset = false;
		bool status=false;
        uint8_t pin_set=0;
		uint8_t pin_reset=0;
        SemaphoreHandle_t Semampore=NULL;
        public:
        Relais( void );

        void begin(uint8_t pin_set, uint8_t pin_reset);
        void begin(uint8_t pin, uint8_t pin_reset, bool inverted_set, bool inverted_reset);
        void begin(uint8_t pin, uint8_t pin_reset, bool inverted_set, bool inverted_reset, SemaphoreHandle_t sem);
        void on();
        void off();
        void SetStatus(bool sta);
        bool GetStatus(void );
        void RegisterSemaphore( SemaphoreHandle_t* SemPtr);
        void UnregisterSemaphore( void  );
        //We need to be able to register an kind of on change.....
    };

#endif