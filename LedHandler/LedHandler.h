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
        void changeIntensity(int);
    private :
        int ledPin;
        int ledState;
        int ledIntensity;
};

#endif //CSZ_LEDHANDLER
