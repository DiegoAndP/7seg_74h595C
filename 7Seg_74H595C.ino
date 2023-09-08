/*
TO DO
    calcular corrente
Doing
    Lógica para calculo de corrente e escolha de qual valor mostrar;
*/

/*
digitList represents an array of 10 numbers from 0 to 9
using decimals values. The values are in order
according to the array positioning.
Eg.: Number 1 is stored in digitList[1]
*/

#include "Meter.h"
#include "VAmeter.h"
/*
==========================================
    Pin definition
==========================================
*/

const int dataPin = 2;
const int latchPin = 3;
const int segPoint = 5;
const int clockPin = 4;
const int buttonPin = 8;
const int digitOrder[4] = {9, 10, 11, 12}; //1000, 100, 10, 1 in order
const int voltageReadPin = A0;
const int currentReadPin = A1;

/*
==========================================
    End of pin definition
==========================================
*/

Digits digit;
float measuredVoltage = 0.0;
float measuredAmps = 0.0;

const byte numberList[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
const byte wordVolt[3] = {62, 92, 56};
const byte wordAmp[4] = {119, 84, 68, 115};

/*
==========================================
    Resistor and Reference Values
==========================================
*/
const float resistor_r1 = 10000.0;
const float resistor_r2 = 2000.0;
const float adc_reference = 5.0;

void setup()
{
    Serial.begin(9600);

    digit.begin();
}

void loop()
{
    measuredVoltage = calculateVoltage(readPin(voltageReadPin));
    measuredAmps = calculateCurrent(readPin(currentReadPin));
    digit.putValues(measuredVoltage, measuredAmps);
    digit.showOnLongPress();
    digit.displayDigits();
}   
