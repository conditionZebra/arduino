#ifndef CSZ_STROBEHANDLER
#define CSZ_STROBEHANDLER

#include <Arduino.h>
#include <LedHandler.h>

class StrobePattern
{
    public :
        StrobePattern() {};
        ~ StrobePattern(){};
        void addSignalPair(int onTime, int offTime){};

};

class StrobeHandler
{
    public :
        StrobeHandler(LedHandler& l) : led(l) {};
        ~StrobeHandler() {};
        void setPattern(StrobePattern& pattern) {}; // todo const
        void execute() {led.setState(LOW);};
    private :
        LedHandler& led;
};

#endif //CSZ_STROBEHANDLER
