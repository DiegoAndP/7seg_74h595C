# 1 "D:\\VsCode\\7Seg_74H595C\\7Seg_74H595C.ino"
/*

TO DO

    calcular corrente

Doing

    Lógica para calculo de corrente e escolha de qual valor mostrar;

*/
# 8 "D:\\VsCode\\7Seg_74H595C\\7Seg_74H595C.ino"
/*

digitList represents an array of 10 numbers from 0 to 9

using decimals values. The values are in order

according to the array positioning.

Eg.: Number 1 is stored in digitList[1]

*/
# 15 "D:\\VsCode\\7Seg_74H595C\\7Seg_74H595C.ino"
# 16 "D:\\VsCode\\7Seg_74H595C\\7Seg_74H595C.ino" 2
# 17 "D:\\VsCode\\7Seg_74H595C\\7Seg_74H595C.ino" 2
/*

==========================================

    Pin definition

==========================================

*/
# 23 "D:\\VsCode\\7Seg_74H595C\\7Seg_74H595C.ino"
const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;
const int segPoint = 5;
const int buttonPin = 8;
const int digitOrder[4] = {9, 10, 11, 12}; //1000, 100, 10, 1 in order
const int voltageReadPin = A0;
const int currentReadPin = A1;

/*

==========================================

    End of pin definition

==========================================

*/
# 38 "D:\\VsCode\\7Seg_74H595C\\7Seg_74H595C.ino"
Digits digit;
float measuredVoltage = 0.0;
float measuredAmps = 0.0;


/*

==========================================

    Resistor and Reference Values

==========================================

*/
# 48 "D:\\VsCode\\7Seg_74H595C\\7Seg_74H595C.ino"
const float resistor_r1 = 10000.0;
const float resistor_r2 = 2000.0;
const float adc_reference = 5.0;
const float rshunt_value = 0.22;

void setup()
{
    Serial.begin(9600);

    digit.begin(COMMON_CATHODE);
}

void loop()
{
    measuredVoltage = calculateVoltage(readPin(voltageReadPin));
    measuredAmps = calculateCurrent(readPin(currentReadPin));
    digit.putValues(measuredVoltage, measuredAmps);
    digit.selectMeter();
    digit.displayDigits();
}
