#line 1 "D:\\VsCode\\7Seg_74H595C\\Meter.cpp"
#include "Arduino.h"
#include "Meter.h"

float _voltageValue;
float _currentValue;
int _valueToDisplay[4];
bool _isVoltageTwoDigits = false;
bool _isButtonPressed = false;
bool _isLongPress = false;
int _buttonLastState = HIGH;
unsigned long _bounceDelay = 5;
unsigned long _currentTime;
unsigned long _lastTime;
unsigned long _pressTime;
unsigned long _releaseTime;
MeterType _typeOfMeter = VOLT;

Digits::Digits()
{
}

void Digits::begin()
{
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

void Digits::toggleMeterType()
{
    unsigned long lasTime = _currentTime;

    if (!digitalRead(buttonPin))
    {
        if (millis() - _currentTime > 50)
        {
            //_buttonState = !_buttonState;
            displayMeterType(800);
        }
    }
}

void Digits::displayDigits()
{
    splitDigits();

    for (int i = 0; i < 4; i++)
    {
        if (!_isVoltageTwoDigits && i == 0 && _typeOfMeter == VOLT | AMP)
        {
            digitalWrite(segPoint, HIGH);
        }
        else if (_isVoltageTwoDigits && i == 1 && _typeOfMeter == VOLT | AMP)
        {
            digitalWrite(segPoint, HIGH);
        }

        else
        {
            digitalWrite(segPoint, LOW);
        }

        digitalWrite(digitOrder[i], HIGH);
        shiftOut(dataPin, clockPin, MSBFIRST, numberList[_valueToDisplay[i]]);
        refreshDigits(20);
        digitalWrite(digitOrder[i], LOW);
    }
}

/*
    Private Functions
*/

void Digits::splitDigits()
{
    unsigned int valueToInt;

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
        if (_currentValue < 1.0)
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
        valueToInt = (_currentValue * _voltageValue) * 100;
        _isVoltageTwoDigits = false;
        break;
    }

    _valueToDisplay[0] = (valueToInt / 1000) % 10;
    _valueToDisplay[1] = (valueToInt / 100) % 10;
    _valueToDisplay[2] = (valueToInt / 10) % 10;
    _valueToDisplay[3] = (valueToInt / 1) % 10;
}

void Digits::refreshDigits(int delayTime)
{
    digitalWrite(latchPin, HIGH);
    delay(delayTime);
    digitalWrite(latchPin, LOW);
}

void Digits::displayMeterType(long delayTime)
{
}

void Digits::showWord(const byte list[])
{
    int size = sizeof(list);

    for (int i = 0; i < size; i++)
    {
        digitalWrite(digitOrder[i], HIGH);
        shiftOut(dataPin, clockPin, MSBFIRST, list[i]);
        refreshDigits(30);
        digitalWrite(digitOrder[i], LOW);
    }
}

void Digits::showOnLongPress()
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
                Serial.println("REturn form WATTS To VOLTS");
                break;

            default:
                _typeOfMeter = WATT;
                Serial.println("MOVE FROM WATHEVER TO WATTS");
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
                    showWord(wordAmp);
                } while (millis() - time < 1500);
                break;

            case AMP:
                time = millis();
                _typeOfMeter = VOLT;

                do
                {
                    showWord(wordVolt);
                } while (millis() - time < 1500);

                break;
            default:
                break;
            }
        }
    }
}