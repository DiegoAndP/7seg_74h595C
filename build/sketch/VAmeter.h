#line 1 "D:\\VsCode\\7Seg_74H595C\\VAmeter.h"
#ifndef VAMETER_H
#define VAMETER_H

#include <Arduino.h>
extern const float resistor_r1;
extern const float resistor_r2;
extern const float adc_reference;

float calculateVoltage(float value);
float calculateCurrent(float value);
float readPin(int analogPin);

#endif