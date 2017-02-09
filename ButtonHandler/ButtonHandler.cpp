#include <ButtonHandler.h>

const long ButtonHandler::longPressDuration;
const int ButtonHandler::flickeringTime;
const int ButtonHandler::doublePressGap;

ButtonHandler::ButtonHandler() : ButtonHandler(2)
{
}

ButtonHandler::ButtonHandler(int pin) :
        buttonPin(pin),
        lastPressed(0),
        longPressed(false),
        waitForDubleTimerStart(0),
        currentTime(0),
        state(HIGH),
        buttonVal(HIGH),
        pressType(NOT_PRESSED)
{
    pinMode(buttonPin,INPUT);
}

ButtonHandler::~ButtonHandler() {}

int ButtonHandler::getPressType()
{
    buttonVal = digitalRead(buttonPin);
    currentTime = millis();

    // Detects a real button press.

    if (buttonVal == LOW)
    {
        if(!lastPressed)        // Marked line. Read bellow to understand why!
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

        lastPressed = 0;
        state = HIGH;

        // This button release is hanled by the longpress part.
        // Just clear stuff.
        if(longPressed)
        {
            longPressed = false;
            waitForDubleTimerStart = 0; //Double press with a long second one? Nope!
            return NOT_PRESSED;
        }
        // Not a button release from a long press.
        // Double press check needed. So we store the release time
        // and wait... Single presses are handled at the bottom of this monster.
        else if(waitForDubleTimerStart == 0)
        {
            waitForDubleTimerStart = currentTime;
            return NOT_PRESSED;
        }
        // If we reach this part it means that
        // - we had a non-zero waitForDubleTimerStart
        // - and we did not handle that because we did not run out of time yet
        // So it is a DOUBLE_PRESS!
        else
        {
            waitForDubleTimerStart = 0;
            return DOUBLE_PRESS;
        }
    }
    // The button is down. Quite down, for a long time.
    // So it's a LONG_PRESS.
    else if(    buttonVal == LOW && 
                state == LOW && 
                currentTime - lastPressed > longPressDuration)
    {
        longPressed = true;
        lastPressed = millis();
        return LONG_PRESS;
    }
    // Button is HIGH and it was before. Waiting for double press ended, we ran out of time.
    // So it's a SINGLE_PRESS.
    else if(    buttonVal == HIGH && 
                state == HIGH && 
                waitForDubleTimerStart != 0 && 
                currentTime - waitForDubleTimerStart > doublePressGap)
    {
        waitForDubleTimerStart = 0;
        return SINGLE_PRESS;
    }

    return NOT_PRESSED;
}
