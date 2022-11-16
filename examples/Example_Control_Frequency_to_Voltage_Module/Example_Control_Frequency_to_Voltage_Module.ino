/***********************************************************************
 * Project      :     Example_Control_Frequency_to_Volage_Module
 * Description  :     Tiny32 Control Frequency to Volage Module with PWM output is 0-10V
 * Hardware     :     tiny32_v3
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/07/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-380-3299
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;

double freq;
String str = "";

/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    mcu.library_version();
    Serial.printf("\r\n**** Example_Control_Frequency_to_Volage_Module ****\r\n");
    mcu.buzzer_beep(2); // frequency range 0-19500Hz
    Serial.printf("Enter Voltage x 0.1 (V) :");
}

/***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{

    char _buff[5];

    /* Get voltage value from Serial port Volt unit */
    while (Serial.available())
    {
        int inChar = Serial.read();
        if (isDigit(inChar))
        {
            str += (char)inChar;
        }

        if (inChar == '\n')
        {
            str.toCharArray(_buff, sizeof(_buff));
            Serial.printf("%0.1f", str.toFloat() * 0.1);
            Serial.println("V");
            double _result = (double)((str.toFloat() * 0.1) - 0.0312) / 0.0082;
            Serial.printf("Freq => %.0fHz\r\n\r\n", _result);
            mcu.Frequency_Out(5, _result);  // pin 5,18,23,19, Not allow for else
            mcu.Frequency_Out(18, _result); // pin 5,18,23,19, Not allow for else
            mcu.Frequency_Out(23, _result); // pin 5,18,23,19, Not allow for else
            mcu.Frequency_Out(19, _result); // pin 5,18,23,19, Not allow for else
            mcu.buzzer_beep(1);
            str = "";
            Serial.printf("Enter Voltage x 0.1 (V) :");
        }
    }
}