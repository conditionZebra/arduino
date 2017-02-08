#include <LedHandler.h>

LedHandler::LedHandler() : ledPin(2), ledState(LOW)
{
    pinMode(ledPin,OUTPUT);
}

LedHandler::LedHandler(int pin) : ledPin(pin), ledState(LOW)
{
    pinMode(ledPin,OUTPUT);
}

LedHandler::LedHandler(int pin, int state) : ledPin(pin), ledState(state)
{
    pinMode(ledPin,OUTPUT);
}

LedHandler::~LedHandler() {}

void LedHandler::setState(int state)
{
    ledState = state; 
    digitalWrite(ledPin,ledState);
    return;
}

void LedHandler::changeState()
{
    ledState = !ledState;
    digitalWrite(ledPin,ledState);
}
