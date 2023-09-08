#line 1 "D:\\VsCode\\7Seg_74H595C\\buttonDebounce.cpp"
#include "buttonDebounce.h"
#include "Meter.h"

unsigned long currentTime;
unsigned long lastTime = 0.0;
unsigned long pressedTime = 0.0;
unsigned long releasedTime = 0.0;
unsigned long bounceDelay = 100;
int currentState = LOW;
int lastState = HIGH;



Button::Button(int pin)
{
    _pin = pin;
}

void Button::showOnLongPress()
{
    currentTime = millis();
    currentState = digitalRead(_pin);

    if (millis() - lastTime > bounceDelay )
    {
        if (currentState == LOW && lastState == HIGH)
        {
           pressedTime = millis();
            
        }
        else if (currentState == HIGH && lastState == LOW)
        {
            releasedTime = millis();
        }

        

    }


}