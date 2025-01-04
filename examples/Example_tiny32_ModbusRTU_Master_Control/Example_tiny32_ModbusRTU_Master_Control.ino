/***********************************************************************
 * Project      :     Example_tiny32_ModbusRTU_Master_Control
 * Description  :     set Address for ModbusRTU [1-253]
 * Hardware     :     tiny32
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/01/2025
 * Revision     :     1.0
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-140-7205
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>

/****************************************/
/*   define modbus register address     */
/* (ตำแหน่งรีเจสเตอร์ที่เก็บค่า parameter ต่างๆ) */
/****************************************/

#define modbus_21_addr 0x28 // 20 ตำแหน่ง Address ค่าที่ต้องการควบคุมตัวที่ 1  Address=40
#define modbus_22_addr 0x2A // 21 ตำแหน่ง Address ค่าที่ต้องการควบคุมตัวที่ 2  Address=42
#define modbus_23_addr 0x2C // 22 ตำแหน่ง Address ค่าที่ต้องการควบคุมตัวที่ 3  Address=44
#define modbus_24_addr 0x2E // 23 ตำแหน่ง Address ค่าที่ต้องการควบคุมตัวที่ 4  Address=46
#define modbus_25_addr 0x30 // 24 ตำแหน่ง Address ค่าที่ต้องการควบคุมตัวที่ 5  Address=48
#define modbus_26_addr 0x32 // 25 ตำแหน่ง Address ค่าที่ต้องการควบคุมตัวที่ 6  Address=50
#define modbus_27_addr 0x34 // 26 ตำแหน่ง Address ค่าที่ต้องการควบคุมตัวที่ 7  Address=52
#define modbus_28_addr 0x35 // 27 ตำแหน่ง Address ค่าที่ต้องการควบคุมตัวที่ 8  Address=54
#define modbus_29_addr 0x38 // 28 ตำแหน่ง Address ค่าที่ต้องการควบคุมตัวที่ 9  Address=56
#define modbus_30_addr 0x3A // 29 ตำแหน่ง Address ค่าที่ต้องการควบคุมตัวที่ 10 Address=58

const uint8_t device_1_addr = modbus_21_addr;
const uint8_t device_2_addr = modbus_22_addr;
const uint8_t device_3_addr = modbus_23_addr;
const uint8_t device_4_addr = modbus_24_addr;
const uint8_t device_5_addr = modbus_25_addr;
const uint8_t device_6_addr = modbus_26_addr;
const uint8_t device_7_addr = modbus_27_addr;
const uint8_t device_8_addr = modbus_28_addr;
const uint8_t device_9_addr = modbus_29_addr;
const uint8_t device_10_addr = modbus_30_addr;

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

tiny32_v3 mcu; // define object

uint8_t id = 1; // current address of ModbusRTU, You can change here if it differance

void read_status()
{
  mcu.tiny32_ModbusRTU_Status(id, value_11, value_12, value_13, value_14, value_15, value_16, value_17, value_18, value_19, value_20);
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

void setup()
{
  Serial.begin(115200);
  Serial.printf("\r\n**** Example_tiny32_ModbusRTU_Master_Control ****\r\n");
  mcu.library_version();
  mcu.tiny32_ModbusRTU_begin(RXD2, TXD2);
  mcu.buzzer_beep(2); // buzzer 2 beeps
}

void loop()
{

  Serial.println("*** device_1: ON ***");
  mcu.tiny32_ModbusRTU_Control(id, device_1_addr, 1);
  read_status();
  vTaskDelay(1000);
  Serial.println("*** device_1: OFF ***");
  mcu.tiny32_ModbusRTU_Control(id, device_1_addr, 0);
  read_status();
  vTaskDelay(1000);

  Serial.println("*** device_2: ON ***");
  mcu.tiny32_ModbusRTU_Control(id, device_2_addr, 1);
  read_status();
  vTaskDelay(1000);
  Serial.println("*** device_2: OFF ***");
  mcu.tiny32_ModbusRTU_Control(id, device_2_addr, 0);
  read_status();
  vTaskDelay(1000);

  Serial.println("*** device_3: ON ***");
  mcu.tiny32_ModbusRTU_Control(id, device_3_addr, 1);
  read_status();
  vTaskDelay(1000);
  Serial.println("*** device_3: OFF ***");
  mcu.tiny32_ModbusRTU_Control(id, device_3_addr, 0);
  read_status();
  vTaskDelay(1000);

  Serial.println("*** device_4: ON ***");
  mcu.tiny32_ModbusRTU_Control(id, device_4_addr, 1);
  read_status();
  vTaskDelay(1000);
  Serial.println("*** device_4: OFF ***");
  mcu.tiny32_ModbusRTU_Control(id, device_4_addr, 0);
  read_status();
  vTaskDelay(1000);

  Serial.println("*** device_5: ON ***");
  mcu.tiny32_ModbusRTU_Control(id, device_5_addr, 1);
  read_status();
  vTaskDelay(1000);
  Serial.println("*** device_5: OFF ***");
  mcu.tiny32_ModbusRTU_Control(id, device_5_addr, 0);
  read_status();
  vTaskDelay(1000);

  Serial.println("*** device_6: ON ***");
  mcu.tiny32_ModbusRTU_Control(id, device_6_addr, 1);
  read_status();
  vTaskDelay(1000);
  Serial.println("*** device_6: OFF ***");
  mcu.tiny32_ModbusRTU_Control(id, device_6_addr, 0);
  read_status();
  vTaskDelay(1000);

  Serial.println("*** device_7: ON ***");
  mcu.tiny32_ModbusRTU_Control(id, device_7_addr, 1);
  read_status();
  vTaskDelay(1000);
  Serial.println("*** device_7: OFF ***");
  mcu.tiny32_ModbusRTU_Control(id, device_7_addr, 0);
  read_status();
  vTaskDelay(1000);

  Serial.println("*** device_8: ON ***");
  mcu.tiny32_ModbusRTU_Control(id, device_8_addr, 1);
  read_status();
  vTaskDelay(1000);
  Serial.println("*** device_8: OFF ***");
  mcu.tiny32_ModbusRTU_Control(id, device_8_addr, 0);
  read_status();
  vTaskDelay(1000);

  Serial.println("*** device_9: ON ***");
  mcu.tiny32_ModbusRTU_Control(id, device_9_addr, 1);
  read_status();
  vTaskDelay(1000);
  Serial.println("*** device_9: OFF ***");
  mcu.tiny32_ModbusRTU_Control(id, device_9_addr, 0);
  read_status();
  vTaskDelay(1000);

  Serial.println("*** device_10: ON ***");
  mcu.tiny32_ModbusRTU_Control(id, device_10_addr, 1);
  read_status();
  vTaskDelay(1000);
  Serial.println("*** device_10: OFF ***");
  mcu.tiny32_ModbusRTU_Control(id, device_10_addr, 0);
  read_status();
  vTaskDelay(1000);
}
