#include "VAmeter.h"

float readPin(int analogPin)
{
    float value = 0.0;
    for (int i = 0; i < 10; i++)
    {
        value += analogRead(analogPin);
    }
    return value / 10;
}

float calculateCurrent(float value)
{
    return (value * (adc_reference / 1023.0)) / rshunt_value;
}

float calculateVoltage(float value)
{
    return (value * (adc_reference / 1023.0) / resistor_r2) * (resistor_r1 + resistor_r2);
}