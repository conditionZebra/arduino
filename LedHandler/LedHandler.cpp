#include <LedHandler.h>

LedHandler::LedHandler() : LedHandler(2,LOW) {}

LedHandler::LedHandler(int pin) : LedHandler(pin, LOW) {}

LedHandler::LedHandler(int pin, int state) : ledPin(pin), ledState(state), ledIntensity(255)
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
    if(ledState == HIGH)
        analogWrite(ledPin,ledIntensity);
    else
       digitalWrite(ledPin,ledState); 
}

void LedHandler::changeIntensity(int newIntensity)
{
    if(ledState == HIGH)
    {
        ledIntensity = newIntensity;
        analogWrite(ledPin,newIntensity);
    }
}
