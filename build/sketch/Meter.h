#line 1 "D:\\VsCode\\7Seg_74H595C\\Meter.h"
#ifndef METER_H
#define METER_H

#include <Arduino.h>

extern const int dataPin;
extern const int latchPin;
extern const int segPoint;
extern const int clockPin;
extern const int buttonPin;
extern const int digitOrder[];

const byte cathodeNumberList[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111}; // 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111
const byte anodeNumberList[10] = {64, 121, 36, 48, 25, 18, 2, 120, 0, 16};      // 0b01000000, 0b01111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b01111000, 0b00000000, 0b00010000
const byte cathodeWordAmp[4] = {119, 84, 68, 115};                              // 0b01110111, 0b01010100, 0b01000100, 0b01110011
const byte anodeWordAmp[4] = {8, 43, 59, 116};                                  // 0b00001000, 0b00101011, 0b00111011, 0b01110100
const byte cathodeWordVolt[3] = {62, 92, 56};
const byte anodeWordVolt[3] = {65, 35, 71}; // 0b01000001, 0b00100011, 0b01000111

enum MeterType
{
        VOLT,
        AMP,
        WATT
};

enum LedMode
{
        COMMON_CATHODE,
        COMMON_ANODE
};

class Digits
{
public:
        Digits();
        void begin(LedMode ledMode);
        void putValues(float voltageValue, float currentValue);
        void displayDigits();
        void selectMeter();

private:
        int _pinOutputState;
        byte numberList[10], wordVolt[3], wordAmp[4];
        bool _isVoltageTwoDigits, _isAmpSelected, _isButtonPressed;
        MeterType _typeOfMeter;
        int _valueToDisplay[4];
        float _voltageValue, _currentValue;
        unsigned long _lastTime;
        void splitDigits();
        void refreshDigits(int delayTime);
        void showWord(byte list[], int size);
};

#endif