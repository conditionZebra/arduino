#ifndef CSZ_LEDHANDLER
#define CSZ_LEDHANDLER

#include <Arduino.h>

class LedHandler
{
    public :
        LedHandler();
        LedHandler(int pin);
        LedHandler(int pin, int state);
        ~LedHandler();
        void setState(int state);
        void changeState();
    private :
        int ledPin;
        int ledState;
};

#endif //CSZ_LEDHANDLER
