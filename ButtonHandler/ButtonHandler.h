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
                            DOUBLE_PRESS,
                            LONG_PRESS
        };

    private :
        int buttonPin;
        long lastPressed;
        bool longPressed;
        long waitForDubleTimerStart;
        long currentTime;
        int state;
        int buttonVal;
        int pressType;

        static const int doublePressGap = 120;
        static const long longPressDuration = 1000;
        static const int flickeringTime = 20;
};

#endif //CSZ_BUTTONHANDLER
