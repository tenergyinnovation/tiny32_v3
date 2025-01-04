/***********************************************************************
 * Project      :     Example_tiny32_ModbusRTU_Master_v2
 * Description  :     Test Master ModbusRTU for interface with tiny32_ModbusRTU_Client
 * Hardware     :     tiny32_v3
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/01/2025
 * Revision     :     1.1
 * Rev1.0       :     Origital
 * Rev1.1       :     Additonal function tiny32_ModbusRTU_Status [04-01-2025]
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-1407205
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

float value_11 = 0;
float value_12 = 0;
float value_13 = 0;
float value_14 = 0;
float value_15 = 0;
float value_16 = 0;
float value_17 = 0;
float value_18 = 0;
float value_19 = 0;
float value_20 = 0;

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

  mcu.tiny32_ModbusRTU_Status(id, value_11, value_12, value_13, value_14, value_15, value_16, value_17, value_18, value_19, value_20);
  vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU_Status(id,value_11,value_12,value_13,value_14,value_15,value_16,value_17,value_18,value_19);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU_Status(id,value_11,value_12,value_13,value_14,value_15,value_16,value_17,value_18);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU_Status(id,value_11,value_12,value_13,value_14,value_15,value_16,value_17);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU_Status(id,value_11,value_12,value_13,value_14,value_15,value_16);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU_Status(id,value_11,value_12,value_13,value_14,value_15);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU_Status(id,value_11,value_12,value_13,value_14);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU_Status(id,value_11,value_12,value_13);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU_Status(id,value_11,value_12);
  // vTaskDelay(1000);

  // mcu.tiny32_ModbusRTU_Status(id,value_11);
  // vTaskDelay(1000);

  Serial.printf("Info: value_11 => %.0f\r\n", value_11);
  Serial.printf("Info: value_12 => %.0f\r\n", value_12);
  Serial.printf("Info: value_13 => %.0f\r\n", value_13);
  Serial.printf("Info: value_14 => %.0f\r\n", value_14);
  Serial.printf("Info: value_15 => %.0f\r\n", value_15);
  Serial.printf("Info: value_16 => %.0f\r\n", value_16);
  Serial.printf("Info: value_17 => %.0f\r\n", value_17);
  Serial.printf("Info: value_18 => %.0f\r\n", value_18);
  Serial.printf("Info: value_19 => %.0f\r\n", value_19);
  Serial.printf("Info: value_20 => %.0f\r\n", value_20);
  Serial.printf("*****************************\r\n");
}