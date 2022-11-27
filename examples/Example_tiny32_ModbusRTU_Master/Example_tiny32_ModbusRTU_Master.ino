/***********************************************************************
 * Project      :     Example_tiny32_ModbusRTU_Master
 * Description  :     Test Master ModbusRTU for interface with tiny32_ModbusRTU_Client
 * Hardware     :     tiny32 v2
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     2/07/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-308-3299
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;

/**************************************/
/*        define global variable      */
/**************************************/
float value_1 = 0;
float value_2 = 0;
float value_3 = 0;
float value_4 = 0;
float value_5 = 0;
float value_6 = 0;
float value_7 = 0;
float value_8 = 0;
float value_9 = 0;
float value_10 = 0;

// ID
byte id = 1; // ID ของบอร์ด *

/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
  Serial.begin(115200);
  mcu.tiny32_ModbusRTU_begin(RXD2, TXD2);
  Serial.printf("*** Example_tiny32_ModbusRTU_Master ***\r\n");
  mcu.library_version();
  Serial.println("done");
  mcu.buzzer_beep(2);
}

/***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{

  mcu.tiny32_ModbusRTU(id, value_1, value_2, value_3, value_4, value_5, value_6, value_7, value_8, value_9, value_10);
  vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU(id,value_1,value_2,value_3,value_4,value_5,value_6,value_7,value_8,value_9);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU(id,value_1,value_2,value_3,value_4,value_5,value_6,value_7,value_8);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU(id,value_1,value_2,value_3,value_4,value_5,value_6,value_7);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU(id,value_1,value_2,value_3,value_4,value_5,value_6);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU(id,value_1,value_2,value_3,value_4,value_5);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU(id,value_1,value_2,value_3,value_4);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU(id,value_1,value_2,value_3);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU(id,value_1,value_2);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU(id,value_1);
  // vTaskDelay(1000);

  Serial.printf("Info: value_1 => %.2f\r\n", value_1);
  Serial.printf("Info: value_2 => %.2f\r\n", value_2);
  Serial.printf("Info: value_3 => %.2f\r\n", value_3);
  Serial.printf("Info: value_4 => %.2f\r\n", value_4);
  Serial.printf("Info: value_5 => %.2f\r\n", value_5);
  Serial.printf("Info: value_6 => %.2f\r\n", value_6);
  Serial.printf("Info: value_7 => %.2f\r\n", value_7);
  Serial.printf("Info: value_8 => %.2f\r\n", value_8);
  Serial.printf("Info: value_9 => %.2f\r\n", value_9);
  Serial.printf("Info: value_10 => %.2f\r\n", value_10);
  Serial.printf("*****************************\r\n");
}