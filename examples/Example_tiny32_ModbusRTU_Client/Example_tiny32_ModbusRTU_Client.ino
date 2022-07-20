/***********************************************************************
 * Project      :     Example_tiny32_ModbusRTU_Client
 * Description  :     Establish tiny32 to Modbus RTC client
 * Hardware     :     tiny32 v2
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     2/07/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * Rev1.1       :     Set and Read ID of ModbusRTU client
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-380-3299
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
#define value_1_addr 0x0000
#define value_2_addr 0x0002
#define value_3_addr 0x0004
#define value_4_addr 0x0006
#define value_5_addr 0x0008
#define value_6_addr 0x000A
#define value_7_addr 0x000C
#define value_8_addr 0x000E
#define value_9_addr 0x0010
#define value_10_addr 0x0012
#define id_addr 0x0020 // 32

/**************************************/
/*   MultiTasking function define     */
/**************************************/
void ReadSensor_Task(void *p); //task for read any sensor
void ModBus_Task(void *p); //task for communication with RS485 modbusRTU

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
unsigned char *chpt;

// ID
#define ID_DEFAULT 1 // default ID
byte id;             // ตัวแปรสำหรับเก็บค่า ID ของบอร์ด *
float id_f;          //ตัวแปรชั่วคราว id ที่เป็นชนิดแบบ float เพื่อนำไปเก็บไว้ในตัวแหน่ง address register ได้

// Register Address*
unsigned int data_register[256]; //ตัวแปรที่ใช้สำหรับเก็บ data เพื่อทำการสือสารไปยัง modbus protocol

/**************************************/
/*        define eeprom               */
/**************************************/
#define EEPROM_SIZE 1024
#define ID_EEPROM 100 //ตำแหน่งเก็ํบค่า ID eeprom ห้ามเขียนทับตำแหน่งนี้ **

/**************************************/
/*           define function          */
/**************************************/
// modbus
void register_update(unsigned int address, float *para); 
uint16_t register_read(unsigned int address);
uint16_t crc16_update(uint16_t crc, uint8_t a);

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
    value_1 = 11.1; //value_1 = Read_sensor1();
    value_2 = 22.2; //value_2 = Read_sensor2();
    value_3 = 33.3; //value_3 = Read_sensor3();
    value_4 = 44.4; //value_4 = Read_sensor4();
    value_5 = 55.5; //value_5 = Read_sensor5();
    value_6 = 66.6; //value_6 = Read_sensor6();
    value_7 = 77.7; //value_7 = Read_sensor7();
    value_8 = 88.8; //value_8 = Read_sensor8();
    value_9 = 99.9; //value_9 = Read_sensor9();
    value_10 = 111.1; //value_10 = Read_sensor10();

    //*** update sensor value to register ***//
    register_update(value_1_addr, &value_1);
    register_update(value_2_addr, &value_2);
    register_update(value_3_addr, &value_3);
    register_update(value_4_addr, &value_4);
    register_update(value_5_addr, &value_5);
    register_update(value_6_addr, &value_6);
    register_update(value_7_addr, &value_7);
    register_update(value_8_addr, &value_8);
    register_update(value_9_addr, &value_9);
    register_update(value_10_addr, &value_10);
    register_update(id_addr, &id_f);
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
  byte _data_send[50];
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

      //        Serial.printf("Debug: _byte_cnt = %d\r\n",_byte_cnt);

      //        for(byte _i=0; _i<sizeof(_data); _i++){
      //            Serial.printf("Debug: _data[%d] = 0x%d\r\n",_i,_data[_i]);
      //          }

      if (_data[0] == id)
      {

        // crc16 check
        for (byte _i = 0; _i < (_byte_cnt - 2); _i++)
        {
          _crc = crc16_update(_crc, _data[_i]);
        }

        //                Serial.printf("Debug: _crc = 0x%X\r\n",_crc);

        _crc_r = _data[_byte_cnt - 1];          // Serial.print(">>"); Serial.println(_crc_r,HEX);
        _crc_r = _crc_r << 8;                   // Serial.print(">>"); Serial.println(_crc_r,HEX);
        _crc_r = _crc_r + _data[_byte_cnt - 2]; // Serial.print(">>"); Serial.println(_crc_r,HEX);

        //                Serial.printf("Debug: _crc_r = 0x%X\r\n",_crc_r);

        if (_crc == _crc_r)
        {

          if (_data[0] == id)
          { //ตรวจสอบว่า ID ตรงกันหรือไม่

            _func = _data[1];
            //                Serial.printf("Debug: _func = 0x%X\r\n",_func);

            if (_data[1] == 0x04) // Read Input Register
            {                     // Read Input Register ตรวจสอบว่าค่า function เท่ากับ 0x04 หรือไม่

              /**ตรวจสอบค่า start address ที่จะให้อ่าน */
              _start_address = _data[2];                  // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
              _start_address = _start_address << 8;       // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
              _start_address = _start_address + _data[3]; // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
              //                    Serial.printf("Debug: _start_address = %d[0x%02X]\r\n",_start_address,_start_address);

              /* ตรวจสอบค่าจำนวน byte ที่จะให้อ่าน */
              _len = _data[4];        // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
              _len = _len << 8;       // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
              _len = _len + _data[5]; // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
              //                    Serial.printf("Debug: _len = %d[0x%02X]\r\n",_len,_len);

              for (byte _i = 0; _i < sizeof(_data_send); _i++)
                _data_send[_i] = 0x00; // clear buffer

              /*เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus*/
              _data_send[0] = id;
              _data_send[1] = 0x04;
              _data_send[2] = _len * 2;

              // read data from register ทำการอ่านค่าต่างๆบน data register
              for (int _i = 0; _i < _len; _i++)
              {
                //                        Serial.printf("register_read[%d] = 0x%04X\r\n",_start_address + _i,register_read(_start_address + _i));
                _data_send[(_i * 2) + 3] = register_read(_start_address + _i) >> 8; // Serial.printf("_data_send[%d] = 0x%02X\r\n",(_i*2)+3,_data_send[(_i*2)+3]);
                _data_send[(_i * 2) + 4] = register_read(_start_address + _i);      // Serial.printf("_data_send[%d] = 0x%02X\r\n",(_i*2)+4,_data_send[(_i*2)+4]);
              }

              // generate CRC16
              _crc = 0xffff;
              for (byte _i = 0; _i < (_len * 2) + 3; _i++)
              {
                _crc = crc16_update(_crc, _data_send[_i]);
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
                Serial.printf("%02X ", _data_send[_i]);
                delay(1);
              }
              Serial.println("");
            }
            else if (_data[1] == 0x06) // write singer
            {
              /**ตรวจสอบค่า start address ที่จะให้อ่าน */
              _start_address = _data[2];                  // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
              _start_address = _start_address << 8;       // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
              _start_address = _start_address + _data[3]; // Serial.printf("Debug: _start_address = 0x%02X\r\n",_start_address);
              // Serial.printf("Debug: _start_address = %d[0x%02X]\r\n", _start_address, _start_address);

              /* ตรวจสอบค่าจำนวน byte ที่จะให้อ่าน */
              _len = _data[4];        // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
              _len = _len << 8;       // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
              _len = _len + _data[5]; // Serial.printf("Debug: _len = 0x%02X\r\n",_len);
              // Serial.printf("Debug: _len(New ID) = %d[0x%02X]\r\n", _len, _len);

              if (_len > 1 || _len < 253)
              {
                EEPROM.writeByte(ID_EEPROM, _len);
                EEPROM.commit();
                id = EEPROM.readByte(ID_EEPROM);
                id_f = id;
                register_update(id_addr, &id_f);
                Serial.printf("Info: Success setting new id => %d\r\n", id);

                for (byte _i = 0; _i < sizeof(_data_send); _i++)
                  _data_send[_i] = 0x00; // clear buffer

                /*เขียนค่าแต่ละ byte ที่จะทำการส่งไปทาง modbus*/
                _data_send[0] = _data[0];
                _data_send[1] = _data[1];
                _data_send[2] = _data[2];
                _data_send[3] = _data[3];
                _data_send[4] = _data[4];
                _data_send[5] = _data[5];
                _data_send[6] = _data[6];
                _data_send[7] = _data[7];

                /* ทำการส่งข้อมุลออกไปทาง modbus */
                for (int _i = 0; _i <= 7; _i++)
                {
                  RS485.write(_data_send[_i]);
                  delay(1);
                  Serial.printf("%02X ", _data_send[_i]);
                  delay(1);
                }
                Serial.println("");
              }
              else
              {
                Serial.printf("Error: id = %d is out of range [1-253]\r\n");
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
  Serial.printf("Info: ID: %.0f\r\n", id_f);
  register_update(id_addr, &id_f);

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

/***********************************************************************
 * FUNCTION:    register_update
 * DESCRIPTION: Update data register
 * PARAMETERS:  unsigned int address,float *para
 * RETURNED:    nothing
 ***********************************************************************/
void register_update(unsigned int address, float *para)
{
  //      Serial.println("---------------------- register_update ----------------------------");
  //      Serial.print("Address: 0x"); Serial.println(address,HEX);
  //      Serial.print("Parameter: "); Serial.println(*para,2);

  chpt = (unsigned char *)&*para;

  data_register[address] = chpt[1] << 8;                             // Serial.println(data_register[address],HEX);
  data_register[address] = data_register[address] ^ chpt[0];         // Serial.println(data_register[address],HEX);
                                                                     // Serial.println(data_register[address+1],HEX);
  data_register[address + 1] = chpt[3] << 8;                         // Serial.println(data_register[address+1],HEX);
  data_register[address + 1] = data_register[address + 1] ^ chpt[2]; // Serial.println(data_register[address+1],HEX);
}

/***********************************************************************
 * FUNCTION:    register_read
 * DESCRIPTION: read data register with 2 byte per time
 * PARAMETERS:  unsigned int address
 * RETURNED:    uint16_t
 ***********************************************************************/
uint16_t register_read(unsigned int address)
{
  uint16_t _data = 0x00;
  _data = data_register[address];
  return _data;
}

/***********************************************************************
 * FUNCTION:    crc16_update
 * DESCRIPTION: CRC16 check
 * PARAMETERS:  uint16_t crc, uint8_t a
 * RETURNED:    uint16_t
 ***********************************************************************/
uint16_t crc16_update(uint16_t crc, uint8_t a)
{
  int i;
  crc ^= a;
  for (i = 0; i < 8; ++i)
  {
    if (crc & 1)
      crc = (crc >> 1) ^ 0xA001;
    else
      crc = (crc >> 1);
  }
  return crc;
}
