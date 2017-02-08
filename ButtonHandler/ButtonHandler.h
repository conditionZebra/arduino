#ifndef CSZ_BUTTONHANDLER
#define CSZ_BUTTONHANDLER

#include <Arduino.h>

class ButtonHandler
{
    public :
        ButtonHandler();
        ButtonHandler(int pin);
        ~ButtonHandler();
        int getPressType();

        enum pressTypes {   NOT_PRESSED = 0,
                            SINGLE_PRESS,
                            DOUBE_PRESS,
                            LONG_PRESS
        };

    private :
        int buttonPin;
        int flickeringTime;
        long lastPressed;
        long lastReleased;
        long longPressDuration;
        long currentTime;
        int state;
        int buttonVal;
        int pressType;
        bool longPressed;
        void setupConstants();
};

#endif //CSZ_BUTTONHANDLER
