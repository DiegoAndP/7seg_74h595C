#ifndef VAMETER_H
#define VAMETER_H

#include <Arduino.h>
extern const float resistor_r1;
extern const float resistor_r2;
extern const float adc_reference;
extern const float rshunt_value;

float calculateVoltage(float value);
float calculateCurrent(float value);
float readPin(int analogPin);

#endif