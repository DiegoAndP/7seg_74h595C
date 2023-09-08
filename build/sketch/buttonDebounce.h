#line 1 "D:\\VsCode\\7Seg_74H595C\\buttonDebounce.h"
#ifndef BUTTONDEBOUNCE_H
#define BUTTONDEBOUNCE_H

#include <Arduino.h>

class Button
{
private:
    int _pin;
public:
    Button(int pin);
    void showOnLongPress();
};

#endif