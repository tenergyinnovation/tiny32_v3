/***********************************************************************
 * Project      :     Example_tiny32_ModbusRTU_Client_v2
 * Description  :     Establish tiny32 to Modbus RTC client
 *                    1. Address 0x00 - 0x12 (modbus_1_addr - modbus_10_addr)
 *                    ตำแหน่งแอดเดรสในการอ่านค่าจากเซนเซอร์ต่างๆ ใช้ function 04(Read Input  Register) ในการอ่านค่า
 *                    2. Address 0x08 - 0x3A (modbus_21_addr - modbus_30_addr)
 *                    ตำแหน่งแอดเดรสในการเขียน เพื่อใช้ควบคุมอุปกรณ์ต่างๆใบระบบ
 *                    ใช้ function 06(write Single Register) ในการเขียนค่า
 *                    3. Address 0x14 - 0x26 (modbus_11_addr - modbus_20_addr)
 *                    ตำแหน่งแอดเดรสในการอ่านและแสดงค่าจากอุปกรณ์ควบคุมในข้อ2 ใช้ function 04(Read Input  Register)
 *                    ในการอ่านค่า
 *
 * Hardware     :     tiny32_v3
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/01/2025
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-1407205
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <EEPROM.h>

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;
HardwareSerial RS485(1);

/****************************************/
/*   define modbus register address     */
/* (ตำแหน่งรีเจสเตอร์ที่เก็บค่า parameter ต่างๆ) */
/****************************************/
#define modbus_1_addr 0x00  // 0 ตำแหน่ง Address ค่าเซนเซอร์ตัวที่ 1  Address=0
#define modbus_2_addr 0x02  // 1 ตำแหน่ง Address ค่าเซนเซอร์ตัวที่ 2  Address=2
#define modbus_3_addr 0x04  // 2 ตำแหน่ง Address ค่าเซนเซอร์ตัวที่ 3  Address=4
#define modbus_4_addr 0x06  // 3 ตำแหน่ง Address ค่าเซนเซอร์ตัวที่ 4  Address=6
#define modbus_5_addr 0x08  // 4 ตำแหน่ง Address ค่าเซนเซอร์ตัวที่ 5  Address=8
#define modbus_6_addr 0x0A  // 5 ตำแหน่ง Address ค่าเซนเซอร์ตัวที่ 6  Address=10
#define modbus_7_addr 0x0C  // 6 ตำแหน่ง Address ค่าเซนเซอร์ตัวที่ 7  Address=12
#define modbus_8_addr 0x0E  // 7 ตำแหน่ง Address ค่าเซนเซอร์ตัวที่ 8  Address=14
#define modbus_9_addr 0x10  // 8 ตำแหน่ง Address ค่าเซนเซอร์ตัวที่ 9  Address=16
#define modbus_10_addr 0x12 // 9 ตำแหน่ง Address ค่าเซนเซอร์ตัวที่ 10 Address=18

#define modbus_11_addr 0x14 // 10 ตำแหน่ง Address ค่าที่ต้องการแสดงสถานะตัวที่ 1   Address=20
#define modbus_12_addr 0x16 // 11 ตำแหน่ง Address ค่าที่ต้องการแสดงสถานะตัวที่ 2   Address=22
#define modbus_13_addr 0x18 // 12 ตำแหน่ง Address ค่าที่ต้องการแสดงสถานะตัวที่ 3   Address=24
#define modbus_14_addr 0x1A // 13 ตำแหน่ง Address ค่าที่ต้องการแสดงสถานะตัวที่ 4   Address=26
#define modbus_15_addr 0x1C // 14 ตำแหน่ง Address ค่าที่ต้องการแสดงสถานะตัวที่ 5   Address=28
#define modbus_16_addr 0x1E // 15 ตำแหน่ง Address ค่าที่ต้องการแสดงสถานะตัวที่ 6   Address=30
#define modbus_17_addr 0x20 // 16 ตำแหน่ง Address ค่าที่ต้องการแสดงสถานะตัวที่ 7   Address=32
#define modbus_18_addr 0x22 // 17 ตำแหน่ง Address ค่าที่ต้องการแสดงสถานะตัวที่ 8   Address=34
#define modbus_19_addr 0x24 // 18 ตำแหน่ง Address ค่าที่ต้องการแสดงสถานะตัวที่ 9   Address=36
#define modbus_20_addr 0x26 // 19 ตำแหน่ง Address ค่าที่ต้องการแสดงสถานะตัวที่ 10  Address=38

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

#define id_addr 0x40 // ตำแหน่ง Address เก็บค่า ModbusRTU ID ของบอร์ด Address = 64

/**************************************/
/*   MultiTasking function define     */
/**************************************/
void ReadSensor_Task(void *p); // task for read any sensor
void ModBus_Task(void *p);     // task for communication with RS485 modbusRTU

/**************************************/
/*        define global variable      */
/*  (ตัวแปรสำหรับเก็บค่า sensor หรือ parat) */
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

unsigned char *chpt;

// ID
#define ID_DEFAULT 1 // default ID
byte id;             // ตัวแปรสำหรับเก็บค่า ID ของบอร์ด *
float id_f;          // ตัวแปรชั่วคราว id ที่เป็นชนิดแบบ float เพื่อนำไปเก็บไว้ในตัวแหน่ง address register ได้

// Register Address*
unsigned int data_register[256]; // ตัวแปรที่ใช้สำหรับเก็บ data เพื่อทำการสือสารไปยัง modbus protocol

/**************************************/
/*        define eeprom               */
/**************************************/
#define EEPROM_SIZE 1024
#define ID_EEPROM 100 // ตำแหน่งเก็ํบค่า ID eeprom ห้ามเขียนทับตำแหน่งนี้ **

/**************************************/
/*           define function          */
/**************************************/

/***********************************************************************
 * FUNCTION:    ReadSensor_Task
 * DESCRIPTION: Multitasking Sensor Reading (อ่านค่าเซนเซอร์)
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void ReadSensor_Task(void *p)
{
    while (1)
    {
        value_1 = random(0, 100) * 0.1;  // value_1 = Read_sensor1();
        value_2 = random(0, 100) * 0.1;  // value_2 = Read_sensor2();
        value_3 = random(0, 100) * 0.1;  // value_3 = Read_sensor3();
        value_4 = random(0, 100) * 0.1;  // value_4 = Read_sensor4();
        value_5 = random(0, 100) * 0.1;  // value_5 = Read_sensor5();
        value_6 = random(0, 100) * 0.1;  // value_6 = Read_sensor6();
        value_7 = random(0, 100) * 0.1;  // value_7 = Read_sensor7();
        value_8 = random(0, 100) * 0.1;  // value_8 = Read_sensor8();
        value_9 = random(0, 100) * 0.1;  // value_9 = Read_sensor9();
        value_10 = random(0, 100) * 0.1; // value_10 = Read_sensor10();

        //*** update sensor value to register ***//
        mcu.register_update(modbus_1_addr, &value_1);
        mcu.register_update(modbus_2_addr, &value_2);
        mcu.register_update(modbus_3_addr, &value_3);
        mcu.register_update(modbus_4_addr, &value_4);
        mcu.register_update(modbus_5_addr, &value_5);
        mcu.register_update(modbus_6_addr, &value_6);
        mcu.register_update(modbus_7_addr, &value_7);
        mcu.register_update(modbus_8_addr, &value_8);
        mcu.register_update(modbus_9_addr, &value_9);
        mcu.register_update(modbus_10_addr, &value_10);

        mcu.register_update(modbus_11_addr, &value_11);
        mcu.register_update(modbus_12_addr, &value_12);
        mcu.register_update(modbus_13_addr, &value_13);
        mcu.register_update(modbus_14_addr, &value_14);
        mcu.register_update(modbus_15_addr, &value_15);
        mcu.register_update(modbus_16_addr, &value_16);
        mcu.register_update(modbus_17_addr, &value_17);
        mcu.register_update(modbus_18_addr, &value_18);
        mcu.register_update(modbus_19_addr, &value_19);
        mcu.register_update(modbus_20_addr, &value_20);

        mcu.register_update(id_addr, &id_f);
        vTaskDelay(1000);
        // Serial.printf("Info: ReadSensor_Task runing\r\n");
    }
}

/***********************************************************************
 * FUNCTION:    ModBus_Task
 * DESCRIPTION: Multitasking Modbus (ทำการสื่อสารบน modbus protocol)
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void ModBus_Task(void *p)
{

    byte _data[20];
    byte _data_send[100]; // จำนวน array เป็นตัวกำหนดจำนวนข้อมุล หรือจำนวน Address ในการเก็บข้อมูล 100/2 = 50 Address [Address=0,  Lenght=50]
    int _byte_cnt = 0;
    unsigned int _crc, _crc_r, _cmd;
    byte _func;
    unsigned int _start_address;
    unsigned int _len;

    while (1)
    {

        if (RS485.available())
        { // receive data from RS485
            for (byte _i = 0; _i < sizeof(_data); _i++)
                _data[_i] = 0x00; // clear buffer
            //        for(byte _i=0; _i<sizeof(_data_send); _i++) _data_send[_i] = 0x00; //clear buffer
            _byte_cnt = 0;
            _crc = 0xFFFF;
            _crc_r = 0xFFFF;
            _func = 0xFF;

            // correct data
            do
            {
                _data[_byte_cnt++] = RS485.read();
            } while (RS485.available() > 0);

            // Debug printing
            /*
            if (_byte_cnt == 8)
            {
                Serial.printf("Debug: _byte_cnt = %d\r\n", _byte_cnt);
                for (byte _i = 0; _i < _byte_cnt; _i++)
                {
                    Serial.printf("Debug: _data[%d] = 0x%02X\r\n", _i, _data[_i]);
                }
                Serial.println("------------------------");
            }
            */

            if (_byte_cnt != 8)
            {
                // Serial.println("Error: data is missing");
            }
            else if (_data[0] == id)
            {

                // crc16 check
                for (byte _i = 0; _i < (_byte_cnt - 2); _i++)
                {
                    _crc = mcu.crc16_update(_crc, _data[_i]);
                }

                //                Serial.printf("Debug: _crc = 0x%X\r\n",_crc);

                _crc_r = _data[_byte_cnt - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
                _crc_r = _crc_r << 8;                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
                _crc_r = _crc_r + _data[_byte_cnt - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);

                //                Serial.printf("Debug: _crc_r = 0x%X\r\n",_crc_r);

                if (_crc == _crc_r)
                {

                    if (_data[0] == id)
                    { // ตรวจสอบว่า ID ตรงกันหรือไม่

                        _func = _data[1];
                        //                Serial.printf("Debug: _func = 0x%X\r\n",_func);

                        if (_data[1] == 0x04) // Read Input Register
                        {                     // Read Input Register ตรวจสอบว่าค่า function เท่ากับ 0x04 หรือไม่

                            /**ตรวจสอบค่า start address ที่จะให้อ่าน */
                            _start_address = _data[2];                  // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
                            _start_address = _start_address << 8;       // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
                            _start_address = _start_address + _data[3]; // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
                            // Serial.printf("Debug: _start_address = %d[0x%02X]\r\n", _start_address, _start_address);

                            /* ตรวจสอบค่าจำนวน byte ที่จะให้อ่าน */
                            _len = _data[4];        // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
                            _len = _len << 8;       // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
                            _len = _len + _data[5]; // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
                            // Serial.printf("Debug: _len = %d[0x%02X]\r\n", _len, _len);

                            for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                _data_send[_i] = 0x00; // clear buffer

                            /*เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus*/
                            _data_send[0] = id;
                            _data_send[1] = 0x04;
                            _data_send[2] = _len * 2;

                            // read data from register ทำการอ่านค่าต่างๆบน data register
                            for (int _i = 0; _i < _len; _i++)
                            {
                                // Serial.printf("register_read[%d] = 0x%04X\r\n", _start_address + _i, register_read(_start_address + _i));
                                _data_send[(_i * 2) + 3] = mcu.register_read(_start_address + _i) >> 8;
                                // Serial.printf("_data_send[%d] = 0x%02X\r\n", (_i * 2) + 3, _data_send[(_i * 2) + 3]);
                                _data_send[(_i * 2) + 4] = mcu.register_read(_start_address + _i);
                                // Serial.printf("_data_send[%d] = 0x%02X\r\n", (_i * 2) + 4, _data_send[(_i * 2) + 4]);
                            }

                            // generate CRC16
                            _crc = 0xffff;
                            for (byte _i = 0; _i < (_len * 2) + 3; _i++)
                            {
                                _crc = mcu.crc16_update(_crc, _data_send[_i]);
                            }

                            // Insert CRC16 to data send
                            //                          Serial.printf("_crc = 0x%02X\r\n",_crc);
                            _data_send[(_len * 2) + 4] = _crc >> 8;
                            _data_send[(_len * 2) + 3] = _crc - _data_send[(_len * 2) + 4] * 0x0100;

                            /* ทำการส่งข้อมุลออกไปทาง modbus */
                            for (int _i = 0; _i < (_len * 2) + 5; _i++)
                            {
                                RS485.write(_data_send[_i]);
                                delay(1);
                                // Serial.printf("%02X ", _data_send[_i]);
                                delay(1);
                            }
                            // Serial.println("");
                        }
                        else if (_data[1] == 0x06) // write singer
                        {
                            bool _respose_ok = false;
                            /**ตรวจสอบค่า start address ที่จะให้อ่าน */
                            _start_address = _data[2];                  // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
                            _start_address = _start_address << 8;       // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
                            _start_address = _start_address + _data[3]; // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
                            Serial.printf("Debug: Address = %d[0x%02X]\r\n", _start_address, _start_address);

                            /* ตรวจสอบค่าจำนวน byte ที่จะให้อ่าน */
                            _len = _data[4];        // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
                            _len = _len << 8;       // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
                            _len = _len + _data[5]; // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
                            Serial.printf("Debug: value = %d[0x%02X]\r\n", _len, _len);

                            if ((_start_address >= modbus_21_addr) && (_len >= 0 && _len < 253))
                            {
                                // กำหนด ID ให้กับ tiny32  Address: 64
                                if (_start_address == id_addr)
                                {
                                    if (_len >= 1 && _len < 253) //ค่า address ของ client modbusRTU อยู่ในช่วง 1 - 253
                                    {
                                        EEPROM.writeByte(ID_EEPROM, _len);
                                        EEPROM.commit();
                                        id = EEPROM.readByte(ID_EEPROM);
                                        id_f = id;
                                        mcu.register_update(id_addr, &id_f);
                                        Serial.printf("Info: Success setting new id => %d\r\n", id);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }
                                // กำหนดค่าให้กับตำแหน่ง control-1 Address: 40
                                else if (_start_address == modbus_21_addr)
                                {

                                    Serial.printf("Info: value => %d\r\n", _len);
                                    if (_len == 0)
                                    {
                                        // mcu.Relay(0);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }

                                    else if (_len == 1)
                                    {
                                        // mcu.Relay(1);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }
                                    else
                                    {
                                        _respose_ok = false;
                                    }

                                    // response back to master
                                    if (_respose_ok)
                                    {
                                        value_11 = _len;
                                        mcu.register_update(modbus_11_addr, &value_11);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }

                                // กำหนดค่าให้กับตำแหน่ง control-2 Address: 42
                                else if (_start_address == modbus_22_addr)
                                {

                                    Serial.printf("Info: value => %d\r\n", _len);
                                    if (_len == 0)
                                    {
                                        // mcu.Relay(0);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }

                                    else if (_len == 1)
                                    {
                                        // mcu.Relay(1);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }
                                    else
                                    {
                                        _respose_ok = false;
                                    }

                                    // response back to master
                                    if (_respose_ok)
                                    {
                                        value_12 = _len;
                                        mcu.register_update(modbus_12_addr, &value_12);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }

                                // กำหนดค่าให้กับตำแหน่ง control-3 Address: 44
                                else if (_start_address == modbus_23_addr)
                                {

                                    Serial.printf("Info: value => %d\r\n", _len);
                                    if (_len == 0)
                                    {
                                        // mcu.Relay(0);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }

                                    else if (_len == 1)
                                    {
                                        // mcu.Relay(1);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }
                                    else
                                    {
                                        _respose_ok = false;
                                    }

                                    // response back to master
                                    if (_respose_ok)
                                    {
                                        value_13 = _len;
                                        mcu.register_update(modbus_13_addr, &value_13);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }

                                // กำหนดค่าให้กับตำแหน่ง control-4 Address: 46
                                else if (_start_address == modbus_24_addr)
                                {

                                    Serial.printf("Info: value => %d\r\n", _len);
                                    if (_len == 0)
                                    {
                                        // mcu.Relay(0);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }

                                    else if (_len == 1)
                                    {
                                        // mcu.Relay(1);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }
                                    else
                                    {
                                        _respose_ok = false;
                                    }

                                    // response back to master
                                    if (_respose_ok)
                                    {
                                        value_14 = _len;
                                        mcu.register_update(modbus_14_addr, &value_14);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }

                                // กำหนดค่าให้กับตำแหน่ง control-5 Address: 48
                                else if (_start_address == modbus_25_addr)
                                {

                                    Serial.printf("Info: value => %d\r\n", _len);
                                    if (_len == 0)
                                    {
                                        // mcu.Relay(0);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }

                                    else if (_len == 1)
                                    {
                                        // mcu.Relay(1);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }
                                    else
                                    {
                                        _respose_ok = false;
                                    }

                                    // response back to master
                                    if (_respose_ok)
                                    {
                                        value_15 = _len;
                                        mcu.register_update(modbus_15_addr, &value_15);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }

                                // กำหนดค่าให้กับตำแหน่ง control-6 Address: 50
                                else if (_start_address == modbus_26_addr)
                                {

                                    Serial.printf("Info: value => %d\r\n", _len);
                                    if (_len == 0)
                                    {
                                        // mcu.Relay(0);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }

                                    else if (_len == 1)
                                    {
                                        // mcu.Relay(1);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }
                                    else
                                    {
                                        _respose_ok = false;
                                    }

                                    // response back to master
                                    if (_respose_ok)
                                    {
                                        value_16 = _len;
                                        mcu.register_update(modbus_16_addr, &value_16);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }

                                // กำหนดค่าให้กับตำแหน่ง control-7 Address: 52
                                else if (_start_address == modbus_27_addr)
                                {

                                    Serial.printf("Info: value => %d\r\n", _len);
                                    if (_len == 0)
                                    {
                                        // mcu.Relay(0);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }

                                    else if (_len == 1)
                                    {
                                        // mcu.Relay(1);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }
                                    else
                                    {
                                        _respose_ok = false;
                                    }

                                    // response back to master
                                    if (_respose_ok)
                                    {
                                        value_17 = _len;
                                        mcu.register_update(modbus_17_addr, &value_17);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }

                                // กำหนดค่าให้กับตำแหน่ง control-8 Address: 54
                                else if (_start_address == modbus_28_addr)
                                {

                                    Serial.printf("Info: value => %d\r\n", _len);
                                    if (_len == 0)
                                    {
                                        // mcu.Relay(0);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }

                                    else if (_len == 1)
                                    {
                                        // mcu.Relay(1);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }
                                    else
                                    {
                                        _respose_ok = false;
                                    }

                                    // response back to master
                                    if (_respose_ok)
                                    {
                                        value_18 = _len;
                                        mcu.register_update(modbus_18_addr, &value_18);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }

                                // กำหนดค่าให้กับตำแหน่ง control-9 Address: 56
                                else if (_start_address == modbus_29_addr)
                                {

                                    Serial.printf("Info: value => %d\r\n", _len);
                                    if (_len == 0)
                                    {
                                        // mcu.Relay(0);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }

                                    else if (_len == 1)
                                    {
                                        // mcu.Relay(1);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }
                                    else
                                    {
                                        _respose_ok = false;
                                    }

                                    // response back to master
                                    if (_respose_ok)
                                    {
                                        value_19 = _len;
                                        mcu.register_update(modbus_19_addr, &value_19);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }

                                // กำหนดค่าให้กับตำแหน่ง control-10 Address: 58
                                else if (_start_address == modbus_30_addr)
                                {

                                    Serial.printf("Info: value => %d\r\n", _len);
                                    if (_len == 0)
                                    {
                                        // mcu.Relay(0);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }

                                    else if (_len == 1)
                                    {
                                        // mcu.Relay(1);
                                        mcu.buzzer_beep(1);
                                        _respose_ok = true;
                                    }
                                    else
                                    {
                                        _respose_ok = false;
                                    }

                                    // response back to master
                                    if (_respose_ok)
                                    {
                                        value_20 = _len;
                                        mcu.register_update(modbus_20_addr, &value_20);

                                        for (byte _i = 0; _i < sizeof(_data_send); _i++)
                                            _data_send[_i] = 0x00; // clear buffer

                                        //--เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus --//
                                        _data_send[0] = _data[0];
                                        _data_send[1] = _data[1];
                                        _data_send[2] = _data[2];
                                        _data_send[3] = _data[3];
                                        _data_send[4] = _data[4];
                                        _data_send[5] = _data[5];
                                        _data_send[6] = _data[6];
                                        _data_send[7] = _data[7];

                                        //-- ทำการส่งข้อมุลออกไปทาง modbus --//
                                        for (int _i = 0; _i <= 7; _i++)
                                        {
                                            RS485.write(_data_send[_i]);
                                            delay(1);
                                            Serial.printf("%02X ", _data_send[_i]);
                                            delay(1);
                                        }
                                        Serial.println("");
                                    }
                                }
                                else
                                {
                                    Serial.printf("Error: Out of range.\r\n");
                                }
                            }
                            else
                            {
                                Serial.printf("Error: Out of range..\r\n");
                            }
                        }
                        else
                        {
                            Serial.printf("Error: Invalid command !!!\n\r");
                        }
                    }
                    else
                    {
                        Serial.printf("Debug: ID error");
                    }
                }
                else
                {
                    Serial.printf("Debug: CRC16 error");
                }
            }

            else
            {
                //            Serial.printf("Debug: _data[0] != %d\r\n",id);
            }
        }

        // Serial.printf("Info: ModBus_Task runing\r\n");
        vTaskDelay(100);
    }
}

/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    RS485.begin(9600, SERIAL_8N1, RXD2, TXD2);

    Serial.printf("\r\n************************************************\n\r");
    Serial.printf("Project      :  tiny32_ModbusRTU Client\n\r");
    Serial.printf("Author       :  Tenergy Innovation Co., Ltd.\n\r");
    Serial.printf("Date         :  17 July 2022\n\r");
    Serial.printf("www          :  https://www.tenergyinnovation.co.th\n\r");
    Serial.printf("Email        :  uten.boonliam@tenergyinnovation.co.th\n\r");
    Serial.printf("TEL          :  +6689-140-7205\n\r");
    Serial.printf("************************************************\n\r");

    Serial.print("Info: EEPROM initial ...");
    if (!EEPROM.begin(EEPROM_SIZE))
    {
        mcu.buzzer_beep(3);
        Serial.println("failed to initialise EEPROM");
        delay(1000000);
    }
    else
    {
        id = EEPROM.readByte(ID_EEPROM);
        if (id == 0xFF || id == 0x00)
        {
            EEPROM.writeByte(ID_EEPROM, ID_DEFAULT);
            EEPROM.commit();
            id = EEPROM.readByte(ID_EEPROM);

        } // incase new eeprom
        Serial.println("done");
    }

    id_f = id;
    Serial.printf("Info: ModbusRTU ID: %.0f\r\n", id_f);
    mcu.register_update(id_addr, &id_f);

    Serial.print("Info: Multitasking initial ...");
    xTaskCreate(&ReadSensor_Task, "ReadSensor_Task", 2048, NULL, 10, NULL);
    xTaskCreate(&ModBus_Task, "ModBus_Task", 2048, NULL, 11, NULL);
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
}
