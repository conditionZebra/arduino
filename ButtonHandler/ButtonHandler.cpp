#include <ButtonHandler.h>

ButtonHandler::ButtonHandler() : buttonPin(2)
{
    setupConstants();
    pinMode(buttonPin,INPUT);
}

ButtonHandler::ButtonHandler(int pin) : buttonPin(pin)
{
    setupConstants();
    pinMode(buttonPin,INPUT);
}

ButtonHandler::~ButtonHandler() {}

void ButtonHandler::setupConstants()
{
    flickeringTime = 20;
    lastPressed = 0;
    lastReleased = 0;
    longPressDuration = 1000;
    longPressed = false;
    state = HIGH;
    pressType = NOT_PRESSED;
}

int ButtonHandler::getPressType()
{
    buttonVal = digitalRead(buttonPin);
    currentTime = millis();
    if (buttonVal == LOW)
    {
        lastReleased = 0;
        if(!lastPressed)        // Marked line.
            lastPressed = currentTime;
        else if(currentTime - lastPressed > flickeringTime)
        {
            state = LOW;
        }
    }
    if(buttonVal == HIGH && state == LOW && lastPressed != 0)
    {
        delay(flickeringTime);  // Let the jitter go. We lose
                                // 20 msecs here only when the
                                // button released. There can
                                // be more sophisticated ways
                                // but it's simple to understand
                                // and we don't lose much resource.
                                // This if() reacts the first HIGH
                                // buttonvalue and sets lastPressed
                                // to 0. Then in the next loop() the
                                // buttonVal can be LOW (jitter)
                                // so marked line above would trigger.
                                // That will trigger the LONG_PRESS
                                // part at the next button press.
                                //
                                // It's true!
                                //
                                // Fckn hard to debug in fact.

        state = HIGH;
        lastPressed = 0;
        if(longPressed)
        {
            longPressed = false;
            return NOT_PRESSED;
        }
        else
            return SINGLE_PRESS;
    }
    else if(buttonVal == LOW && state == LOW && currentTime - lastPressed > longPressDuration)
    {
        longPressed = true;
        lastPressed = millis();
        return LONG_PRESS;
    }

    return NOT_PRESSED;
}
