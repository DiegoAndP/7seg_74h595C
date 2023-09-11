#line 1 "D:\\VsCode\\7Seg_74H595C\\Meter.cpp"
#include "Arduino.h"
#include "Meter.h"

byte numberList[10];
byte wordAmp[4];
byte wordVolt[3];
int _pinOutputState;

float _voltageValue;
float _currentValue;
int _valueToDisplay[4];
bool _isVoltageTwoDigits = false;
bool isVoltageThreeDigits = false;
bool _isButtonPressed = false;
unsigned long _lastTime;
MeterType _typeOfMeter = VOLT;

Digits::Digits()
{
}

void Digits::begin(LedMode ledMode)
{

    switch (ledMode)
    {
    case COMMON_CATHODE:

        for (int i = 0; i < 10; i++)
        {
            numberList[i] = cathodeNumberList[i];
        }

        for (int i = 0; i < 4; i++)
        {
            wordAmp[i] = cathodeWordAmp[i];
        }

        for (int i = 0; i < 3; i++)
        {
            wordVolt[i] = cathodeWordVolt[i];
        }
        _pinOutputState = HIGH;

        break;

    case COMMON_ANODE:

        for (int i = 0; i < 10; i++)
        {
            numberList[i] = anodeNumberList[i];
        }

        for (int i = 0; i < 4; i++)
        {
            wordAmp[i] = anodeWordAmp[i];
        }

        for (int i = 0; i < 3; i++)
        {
            wordVolt[i] = anodeWordVolt[i];
        }
        _pinOutputState = LOW;

    default:
        break;
    }

    const int pinList[] = {dataPin, latchPin, clockPin, segPoint};

    for (int i = 0; i < 4; i++)
    {
        pinMode(pinList[i], OUTPUT);
    }
    for (int i = 0; i < 4; i++)
    {
        pinMode(digitOrder[i], OUTPUT);
    }

    pinMode(buttonPin, INPUT);
}

void Digits::putValues(float voltageValue, float currentValue)
{
    _voltageValue = voltageValue;
    _currentValue = currentValue;
}

void Digits::displayDigits()
{
    splitDigits();

    for (int i = 0; i < 4; i++)
    {
        if (!_isVoltageTwoDigits && i == 0 && _typeOfMeter == VOLT | AMP | WATT && !isVoltageThreeDigits)
        {
            digitalWrite(segPoint, _pinOutputState);
        }
        else if (_isVoltageTwoDigits && i == 1 && _typeOfMeter == VOLT | AMP | WATT)
        {
            digitalWrite(segPoint, _pinOutputState);
        }
        else if (isVoltageThreeDigits && i == 2 && _typeOfMeter == WATT)
        {
            digitalWrite(segPoint, _pinOutputState);
        }

        else
        {
            digitalWrite(segPoint, !_pinOutputState);
        }

        digitalWrite(digitOrder[i], _pinOutputState);
        shiftOut(dataPin, clockPin, MSBFIRST, numberList[_valueToDisplay[i]]);
        refreshDigits(10);
        digitalWrite(digitOrder[i], !_pinOutputState);
    }
}

/*
    Private Functions
*/

void Digits::splitDigits()
{
    unsigned int valueToInt;
    float wattValue = _voltageValue * _currentValue;

    switch (_typeOfMeter)
    {
    case VOLT:
        if (_voltageValue < 9.99)
        {
            valueToInt = _voltageValue * 1000;
            _isVoltageTwoDigits = false;
        }
        else
        {
            valueToInt = _voltageValue * 100;
            _isVoltageTwoDigits = true;
        }
        break;

    case AMP:
        if (_currentValue < 9.99)
        {
            valueToInt = _currentValue * 1000;
            _isVoltageTwoDigits = false;
        }
        else
        {
            valueToInt = _currentValue * 100;
            _isVoltageTwoDigits = true;
        }
        break;
    case WATT:

        if (wattValue < 9.99)
        {

            valueToInt = wattValue * 1000;
            _isVoltageTwoDigits = false;
        }
        else if (wattValue > 9.99 && wattValue < 99.99)
        {
            valueToInt = wattValue * 100;
            _isVoltageTwoDigits = true;
        }
        else
        {
            valueToInt = wattValue * 10;
            _isVoltageTwoDigits = false;
            isVoltageThreeDigits = true;
        }
        break;
    default:
        break;
    }

    _valueToDisplay[0] = (valueToInt / 1000) % 10;
    _valueToDisplay[1] = (valueToInt / 100) % 10;
    _valueToDisplay[2] = (valueToInt / 10) % 10;
    _valueToDisplay[3] = (valueToInt / 1) % 10;
}

void Digits::refreshDigits(int delayTime)
{
    unsigned long lastTime = millis();
    while (millis() - lastTime < delayTime)
    {
        digitalWrite(latchPin, HIGH);
    }
    digitalWrite(latchPin, LOW);
}

void Digits::showWord(byte list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        digitalWrite(digitOrder[i], _pinOutputState);
        shiftOut(dataPin, clockPin, MSBFIRST, list[i]);
        refreshDigits(10);
        digitalWrite(digitOrder[i], !_pinOutputState);
    }
}

void Digits::selectMeter()
{
    if (digitalRead(buttonPin) == LOW && !_isButtonPressed)
    {
        _lastTime = millis();
        _isButtonPressed = true;
    }

    if (digitalRead(buttonPin) == HIGH && _isButtonPressed)
    {
        unsigned long time;
        unsigned long timePressed = (millis() - _lastTime);
        _isButtonPressed = false;

        if (timePressed > 1000 && !_isButtonPressed)
        {
            switch (_typeOfMeter)
            {
            case WATT:
                _typeOfMeter = VOLT;
                break;

            default:
                _typeOfMeter = WATT;
                break;
            }
        }
        else
        {
            switch (_typeOfMeter)
            {
            case VOLT:
                time = millis();
                _typeOfMeter = AMP;

                do
                {
                    showWord(wordAmp, 4);
                } while (millis() - time < 1000);
                break;

            case AMP:
                time = millis();
                _typeOfMeter = VOLT;

                do
                {
                    showWord(wordVolt, 3);
                } while (millis() - time < 1000);

                break;
            default:
                break;
            }
        }
    }
}
