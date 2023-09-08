#ifndef METER_H
#define METER_H

#include <Arduino.h>

extern const int dataPin;
extern const int latchPin;
extern const int segPoint;
extern const int clockPin;
extern const int buttonPin;
extern const int digitOrder[];

extern const byte numberList[];
extern const byte wordAmp[];
extern const byte wordVolt[]; 

enum MeterType {
        VOLT,
        AMP,
        WATT
};


class Digits
{
public:
        Digits();
        void begin();
        void putValues(float voltageValue, float currentValue);
        void toggleMeterType();
        void displayDigits();
        void showOnLongPress();

private:
        int _buttonLastState;
        bool _isVoltageTwoDigits, _isAmpSelected, _isLongPress, _isButtonActive;
        MeterType _typeOfMeter;
        int _valueToDisplay[4];
        float _voltageValue, _currentValue;
        unsigned long _currentTime, _lastTime, _pressTime, _releaseTime, _bounceDelay;
        void splitDigits();
        void refreshDigits(int delayTime);
        void showWord(const byte list[]);
        void displayMeterType(long duration);

};

#endif