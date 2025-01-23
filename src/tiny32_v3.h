/***********************************************************************
 * File         :     tiny32_v3.h
 * Description  :     Class for Hardware config and function for tiny32_v3 module
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     23 Nov 2021
 * Revision     :     3.17.3
 * Rev1.0       :     Original
 * Rev1.1       :     Add TimeStamp_minute
 *                    Add TimeStamp_24hr_minute
 * Rev1.2             Add EC RS485 sensor
 * Rev1.3             Change define switch to int
 * Rev1.4       :     Add EC sensor (RS485)
 * Rev1.5       :     Add PZEM-016 Energy Meter AC
 *                    Add PZEM-003 Energy Meter DC
 *                    Add rs485_2.begin(9600, SERIAL_8N2, RXD2, TXD2) for PZEM-003
 * Rev1.6             Intial board to BuildIN LED = > LOW
 * Rev1.7       :     Fix bug for PZEM-003 and PZEM-016 were read data error
 * Rev1.8       :     Add PZEM-003_begin, PZEM-016_begin and ec_modbusRTU_begin for initial set RS485 pin
 * Rev3.0       :     Major change hardware from tiny32_v2.0 to tiny32_v3.0
 *                    Add WTR10_E(SHT20) temperature and humidity sensor (RS485)
 * Rev3.1       :     Add XY-MD02(SHT20) temperature and humidity sensor (RS485)
 * Rev3.2       :     Add SOIL MOISTURE PR-3000-H-N01 sensor (RS485) fix id = 1, baud rate = 4800
 * Rev3.3       :     Add RS485 Water Flow Meter RS485 MODBUS output
 * Rev3.4       :     Add PYR20-Solar Radiation/Pyranometer Sensor, RS485, Modbus
 * Rev3.5       :     Add tiny32 ModbusRTU communication
 * Rev3.5.1     :     Fix bug for modbusRTU by relay 300mS after write modbus RTU (complier of some computer problem)
 * Rev3.5.2     :     Add Example_OTA.ino
 * Rev3.5.3     :     Revise code for Add RS485 Water Flow Meter RS485 MODBUS output (Rev3.3)
 * Rev3.6       :     Add ENenergic ModbusRTU Power Meter
 * Rev3.7       :     Add Schneider EasyLogic PM2xxx Digital Power Meter
 * Rev3.8       :     Add EASTRON Powermeter model : SDM1210CT
 * Rev3.8.1     :     fix bug pzem-016 and pzem-003
 * Rev3.9       :     Frequency_Out function for control Frequency to Volage Module with PWM output is 0-10V
 * Rev3.10      :     Add Wind speed sensor Model RS-FS-N01 485 type [PR-3000FSJT-N01]
 * Rev3.10.1    :     Revise and improve of SDM1210CT
 * Rev3.11      :     Add EASTRON Powermeter 3-phase model :SDM630MCT
 * Rev3.12      :     Add Chiller_R717 ModbusRTU [27-04-2024]
 * Rev3.12.1    :     Add Function of EASTRON Powermeter 3-phase
 * Rev3.13      :     Add Test Bluetooth BLE Speed Sensor Module: BRC01-RS485, BRC01-RS232 [08-12-2024]
 * Rev3.14      :     Add Inverter ATESS ModbusRUT [28-04-2024]
 * Rev3.15      :     Add ModbusRTU relay module [17-12-2024]
 * Rev3.16      :     Add TF-Luna ToF LiDAR Module - 8 meters Distance Sensor [22-12-2024]
 * Rev3.17      :     Additional function and example for tiny32 ModbusRTU [04-01-2025]
 * Rev3.17.1    :     - Add Example for tiny32_ModbusRTU [04-01-2025]
 *                    - Add Function new tiny32_ModbusRTU 
 * Rev3.17.2    :     Fix bug Bluetooth BLE Speed Sensor Module: BRC01 can read Forward and Reverse speed [14-01-2025]
 *                    revise function BRC01_getData
 * Rev3.17.3    :     Fix bug delay time for function tiny32_ModbusRTU_Control [Line: 14690] [23-01-2025]   
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     089-140-7205
 ***********************************************************************/

#ifndef TINY32_H
#define TINY32_H
#include "Ticker.h"

class tiny32_v3
{
private:
#define version_c "3.17.3"

public:

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
/*           GPIO define              */
/**************************************/
#define RXD2 16
#define TXD2 17
#define RXD3 27
#define TXD3 26
#define SW1 34
#define SW2 35
#define RELAY 25
#define LED_IO4 4
#define LED_IO12 12
#define SLID_SW 36
#define BUZZER 13

    tiny32_v3(/* args */);
    void Relay(bool state);
    void RedLED(bool state);
    void BlueLED(bool state);
    void BuildinLED(bool state);
    void buzzer_beep(int times);
    bool Sw1(void);
    bool Sw2(void);
    bool Slid_sw(void);
    void library_version(void);

private:
    uint8_t _resolution_bit;
    // uint16_t crc16_update(uint16_t crc, uint8_t a);
    unsigned char *chpt;
    // Register Address*
    unsigned int data_register[256]; // ตัวแปรที่ใช้สำหรับเก็บ data เพื่อทำการสือสารไปยัง modbus protocol

    int dist;     /*----actual distance measurements of LiDAR---*/
    int strength; /*----signal strength of LiDAR----------------*/
    float temprature;
    unsigned char check;        /*----save check value------------------------*/
    unsigned char uart[9];      /*----save data measured by LiDAR-------------*/
    const int HEADER = 0x59;    /*----frame header of data package------------*/
    int rec_debug_state = 0x01; // receive state for frame

public:
    void TickBlueLED(float second);
    void TickRedLED(float second);
    void TickBuildinLED(float second);
    bool PWM_Setup(uint8_t channel, double freq, uint8_t resolution_bit, uint8_t pin);
    bool PWM_Drive(uint8_t channel, uint8_t percentage);
    bool Frequency_Out(uint8_t pin, double freq);
    uint16_t TimeStamp_minute_encode(uint16_t y, uint8_t m, uint8_t d, uint8_t h, uint8_t mi);
    uint16_t TimeStamp_24hr_encode(uint16_t h, uint16_t mi);
    void TimeStamp_hour_minute_decode(uint16_t timestemp, uint16_t &h, uint16_t &mi);
    uint16_t crc16_update(uint16_t crc, uint8_t a);

private:
    uint16_t ec_modbusRTU(uint8_t id);
    bool ec_modbusRTU_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);

public:
    /* PZEM-016 Modbus RTU AC power meter module */
    bool PZEM_016(uint8_t id, float &volt, float &amp, float &power, uint32_t &energy, float &freq, float &pf);
    float PZEM_016_Volt(uint8_t id);
    float PZEM_016_Amp(uint8_t id);
    float PZEM_016_Power(uint8_t id);
    int16_t PZEM_016_Energy(uint8_t id);
    float PZEM_016_Freq(uint8_t id);
    float PZEM_016_PF(uint8_t id);
    bool PZEM_016_ResetEnergy(uint8_t id);
    int8_t PZEM_016_SetAddress(uint8_t id, uint8_t new_id);
    int8_t PZEM_016_SearchAddress(void);
    bool PZEM_016_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);

    /* PZEM-003 Modbus RTU DC power meter module */
    bool PZEM_003(uint8_t id, float &volt, float &amp, float &power, uint32_t &energy);
    float PZEM_003_Volt(uint8_t id);
    float PZEM_003_Amp(uint8_t id);
    float PZEM_003_Power(uint8_t id);
    int16_t PZEM_003_Energy(uint8_t id);
    bool PZEM_003_ResetEnergy(uint8_t id);
    int8_t PZEM_003_SetAddress(uint8_t id, uint8_t new_id);
    int8_t PZEM_003_SearchAddress(void);
    bool PZEM_003_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);

    /* WTR10-E Modbus RTU Temperature and Humidity sensor module */
    bool WTR10_E_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    bool WTR10_E(uint8_t id, float &temp, float &humi);
    float WTR10_E_tempeature(uint8_t id);
    float WTR10_E_humidity(uint8_t id);

    /* XY-MD02 Modbus RTU Temperature and Humidity sensor module */
    bool XY_MD02_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    bool XY_MD02(uint8_t id, float &temp, float &humi);
    float XY_MD02_tempeature(uint8_t id);
    float XY_MD02_humidity(uint8_t id);
    int8_t XY_MD02_searchAddress(void);
    int8_t XY_MD02_SetAddress(uint8_t id, uint8_t new_id);

    /* SOIL MOISTURE PR-3000-H-N01 sensor (RS485) module */
    bool PR3000_H_N01_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    bool PR3000_H_N01(float &temp, float &humi);
    float PR3000_H_N01_tempeature();
    float PR3000_H_N01_humidity();

    /* RS485 Water Flow Meter RS485 MODBUS output  */
    bool WATER_FLOW_METER_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t WATER_FLOW_METER_searchAddress(void);
    int8_t WATER_FLOW_METER_SetAddress(uint8_t id, uint8_t new_id);
    float WATER_FLOW_METER(uint8_t id);

    /* PYR20-Solar Radiation/Pyranometer Sensor, RS485, Modbus */
    bool PYR20_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t PYR20_searchAddress(void);
    int8_t PYR20_SetAddress(uint8_t id, uint8_t new_id);
    int16_t PYR20_read(uint8_t id);

    /* tiny32 ModbusRTU communication*/
    bool tiny32_ModbusRTU_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t tiny32_ModbusRTU_searchAddress(void);
    int8_t tiny32_ModbusRTU_searchAddress_v2(void);
    int8_t tiny32_ModbusRTU_setAddress(uint8_t id, uint8_t new_id);
    int8_t tiny32_ModbusRTU_setAddress_v2(uint8_t id, uint8_t new_id);
    bool tiny32_ModbusRTU_Control(uint8_t id, uint8_t address, uint8_t value);
    //------
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8, float &val9, float &val10);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8, float &val9);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3);
    bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2);
    bool tiny32_ModbusRTU(uint8_t id, float &val1);
    //--------
    bool tiny32_ModbusRTU_Status(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8, float &val9, float &val10);
    bool tiny32_ModbusRTU_Status(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8, float &val9);
    bool tiny32_ModbusRTU_Status(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8);
    bool tiny32_ModbusRTU_Status(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7);
    bool tiny32_ModbusRTU_Status(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6);
    bool tiny32_ModbusRTU_Status(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5);
    bool tiny32_ModbusRTU_Status(uint8_t id, float &val1, float &val2, float &val3, float &val4);
    bool tiny32_ModbusRTU_Status(uint8_t id, float &val1, float &val2, float &val3);
    bool tiny32_ModbusRTU_Status(uint8_t id, float &val1, float &val2);
    bool tiny32_ModbusRTU_Status(uint8_t id, float &val1);
    //----
    uint16_t register_read(unsigned int address);
    void register_update(unsigned int address, float *para);
    void register_update(unsigned int address, uint8_t *para);

    /* Enenergic ModbusRTU PowerMeter*/
    bool ENenergic_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t ENenergic_searchAddress(void);
    int8_t ENenergic_setAddress(uint8_t id, uint8_t new_id);
    float ENenergic_getTemperature(uint8_t id);
    bool ENenergic_Volt_L_N(uint8_t id, float &L1_N, float &L2_N, float &L3_N);
    bool ENenergic_Volt_L_L(uint8_t id, float &L1_L2, float &L2_L3, float &L3_L1);
    bool ENenergic_Current_L(uint8_t id, float &L1, float &L2, float &L3);
    float ENenergic_NeutralCurrent(uint8_t id);
    float ENenergic_Freq(uint8_t id);
    bool ENenergic_PhaseVolt_Angle(uint8_t id, float &L1, float &L2, float &L3);
    bool ENenergic_PhaseCurrent_Angle(uint8_t id, float &L1, float &L2, float &L3);

    /* Schneider EasyLogic PM2xxx Digital Power Meter */
    bool SchneiderPM2xxx_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t SchneiderPM2xxx_searchAddress(void);

    bool SchneiderPM2xxx_MeteringSetup(void);

    float SchneiderPM2xxx_CurrentA(uint8_t id);
    float SchneiderPM2xxx_CurrentB(uint8_t id);
    float SchneiderPM2xxx_CurrentC(uint8_t id);
    float SchneiderPM2xxx_CurrentN(uint8_t id);
    float SchneiderPM2xxx_CurrentG(uint8_t id);
    float SchneiderPM2xxx_CurrentAvg(uint8_t id);
    float SchneiderPM2xxx_CurrentUnblanceA(uint8_t id);
    float SchneiderPM2xxx_CurrentUnblanceB(uint8_t id);
    float SchneiderPM2xxx_CurrentUnblanceC(uint8_t id);
    float SchneiderPM2xxx_CurrentUnblanceWorst(uint8_t id);

    float SchneiderPM2xxx_Voltage_AB(uint8_t id);
    float SchneiderPM2xxx_Voltage_BC(uint8_t id);
    float SchneiderPM2xxx_Voltage_CA(uint8_t id);
    float SchneiderPM2xxx_Voltage_LL_Avg(uint8_t id);
    float SchneiderPM2xxx_Voltage_AN(uint8_t id);
    float SchneiderPM2xxx_Voltage_BN(uint8_t id);
    float SchneiderPM2xxx_Voltage_CN(uint8_t id);
    float SchneiderPM2xxx_Voltage_LN_Avg(uint8_t id);

    float SchneiderPM2xxx_VoltageUnblance_AB(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_BC(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_CA(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_LL_Worst(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_AN(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_BN(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_CN(uint8_t id);
    float SchneiderPM2xxx_VoltageUnblance_LN_Worst(uint8_t id);

    float SchneiderPM2xxx_ActivePowerA(uint8_t id);
    float SchneiderPM2xxx_ActivePowerB(uint8_t id);
    float SchneiderPM2xxx_ActivePowerC(uint8_t id);
    float SchneiderPM2xxx_ActivePowerTotal(uint8_t id);

    float SchneiderPM2xxx_ReactivePowerA(uint8_t id);
    float SchneiderPM2xxx_ReactivePowerB(uint8_t id);
    float SchneiderPM2xxx_ReactivePowerC(uint8_t id);
    float SchneiderPM2xxx_ReactivePowerTotal(uint8_t id);

    float SchneiderPM2xxx_ApparentPowerA(uint8_t id);
    float SchneiderPM2xxx_ApparentPowerB(uint8_t id);
    float SchneiderPM2xxx_ApparentPowerC(uint8_t id);
    float SchneiderPM2xxx_ApparentPowerTotal(uint8_t id);

    float SchneiderPM2xxx_PowerFactorA(uint8_t id);
    float SchneiderPM2xxx_PowerFactorB(uint8_t id);
    float SchneiderPM2xxx_PowerFactorC(uint8_t id);
    float SchneiderPM2xxx_PowerFactorTotal(uint8_t id);

    float SchneiderPM2xxx_Freq(uint8_t id);

    /* EASTRON SDM120CT Modbus 1-Phase Powermeter */
    bool SDM120CT_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t SDM120CT_searchAddress(void);
    float SDM120CT_Volt(uint8_t id);
    float SDM120CT_Freq(uint8_t id);
    float SDM120CT_Power(uint8_t id);
    float SDM120CT_Current(uint8_t id);
    float SDM120CT_Total_Energy(uint8_t id);
    float SDM120CT_POWER_FACTOR(uint8_t id);

    /* Wind speed sensor [PR-3000FSJT-N01] */
    bool tiny32_WIND_RSFSN01_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t tiny32_WIND_RSFSN01_searchAddress(void);
    int8_t tiny32_WIND_RSFSN01_setAddress(uint8_t id, uint8_t new_id);
    float tiny32_WIND_RSFSN01_SPEED(uint8_t id);

    /* EASTRON SDM630MCT Modbus 3-Phase Powermeter */
    bool SDM630MCT_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    int8_t SDM630MCT_searchAddress(void);

    float SDM630MCT_L1_Volt(uint8_t id); // 30000 - 30001 [ID 04 00 00 00 02 ]
    float SDM630MCT_L2_Volt(uint8_t id); // 30002 - 30003 [ID 04 00 02 00 02 ]
    float SDM630MCT_L3_Volt(uint8_t id); // 30004 - 30005 [ID 04 00 04 00 02 ]

    float SDM630MCT_L1_Current(uint8_t id); // 30006 - 30007 [ID 04 00 06 00 02 ]
    float SDM630MCT_L2_Current(uint8_t id); // 30008 - 30009 [ID 04 00 08 00 02 ]
    float SDM630MCT_L3_Current(uint8_t id); // 300A0 - 300A1 [ID 04 00 0A 00 02 ]

    float SDM630MCT_L1_Watt(uint8_t id); // 300C0 - 3000D [ID 04 00 0C 00 02 ]
    float SDM630MCT_L2_Watt(uint8_t id); // 3000E - 3000F [ID 04 00 0E 00 02 ]
    float SDM630MCT_L3_Watt(uint8_t id); // 30010 - 30011 [ID 04 00 10 00 02 ]

    float SDM630MCT_L1_VA(uint8_t id); // 30012 - 30013 [ID 04 00 12 00 02 ]
    float SDM630MCT_L2_VA(uint8_t id); // 30014 - 30015 [ID 04 00 14 00 02 ]
    float SDM630MCT_L3_VA(uint8_t id); // 30016 - 30017 [ID 04 00 16 00 02 ]

    float SDM630MCT_L1_VAr(uint8_t id); // 30018 - 30019 [ID 04 00 18 00 02 ]
    float SDM630MCT_L2_VAr(uint8_t id); // 3001A - 3001B [ID 04 00 1A 00 02 ]
    float SDM630MCT_L3_VAr(uint8_t id); // 3001C - 3001D [ID 04 00 1C 00 02 ]

    float SDM630MCT_L1_PF(uint8_t id); // 3001E - 3001F [ID 04 00 1E 00 02 ]
    float SDM630MCT_L2_PF(uint8_t id); // 30020 - 30021 [ID 04 00 20 00 02 ]
    float SDM630MCT_L3_PF(uint8_t id); // 30022 - 30023 [ID 04 00 22 00 02 ]

    float SDM630MCT_Freq(uint8_t id); // 30046 - 30047 [ID 04 00 46 00 02 ]

    float SDM630MCT_Sum_Current(uint8_t id); // 30030 - 30031 [ID 04 00 30 00 02 ]
    float SDM630MCT_Total_Watt(uint8_t id);  // 30034 - 30035 [ID 04 00 34 00 02 ]
    float SDM630MCT_Total_VA(uint8_t id);    // 300057 - 30058 [ID 04 00 38 00 02 ]
    float SDM630MCT_Total_VAr(uint8_t id);   // 30061 - 30062 [ID 04 00 3C 00 02 ]

    float SDM630MCT_L1_Import_kWh(uint8_t id);    // 30030 - 30031 [ID 04 00 5A 00 02 ]
    float SDM630MCT_L2_Import_kWh(uint8_t id);    // 30030 - 30031 [ID 04 00 5C 00 02 ]
    float SDM630MCT_L3_Import_kWh(uint8_t id);    // 30030 - 30031 [ID 04 00 5E 00 02 ]
    float SDM630MCT_Total_Import_kWh(uint8_t id); // 30030 - 30031 [ID 04 00 4A 00 02 ]

    /* Chiller R717 ModbusRTU for Read sensor */
    bool CHILLER_R717_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);

    float CHILLER_R717_AI01_CHILLED_IN(uint8_t id);
    float CHILLER_R717_AI02_CHILLED_OUT(uint8_t id);
    float CHILLER_R717_AI03_COOLED_IN(uint8_t id);
    float CHILLER_R717_AI04_COOLED_OUT(uint8_t id);
    float CHILLER_R717_AI05_SUCTION_TEMP(uint8_t id);

    float CHILLER_R717_AI06_DISCHARGE_TEMP(uint8_t id);
    float CHILLER_R717_AI08_COND_PRESS(uint8_t id);
    float CHILLER_R717_AI10_EVAP_PRESS(uint8_t id);
    float CHILLER_R717_Slurry1_Temp(uint8_t id);
    float CHILLER_R717_Slurry2_Temp(uint8_t id);

    float CHILLER_R717_Slurry3_Temp(uint8_t id);
    float CHILLER_R717_Slurry4_Temp(uint8_t id);
    float CHILLER_R717_Coil_Temp(uint8_t id);
    float CHILLER_R717_Room_Temp(uint8_t id);
    float CHILLER_R717_CURRENT_COMP(uint8_t id);

    float CHILLER_R717_VOLT_COMP(uint8_t id);
    float CHILLER_R717_FREQ_COMP(uint8_t id);
    float CHILLER_R717_POWER_COMP(uint8_t id);
    float CHILLER_R717_PER_COMP(uint8_t id);
    float CHILLER_R717_HOUR_CHILLED_PUMP(uint8_t id);

    float CHILLER_R717_HOUR_COMP(uint8_t id);
    float CHILLER_R717_HOUR_COOLED_PUMP(uint8_t id);
    float CHILLER_R717_HOUR_COOLING_TOWER(uint8_t id);
    float CHILLER_R717_SP_ROOM(uint8_t id);
    float CHILLER_R717_TOTAL_KW(uint8_t id);

    /* Bluetooth BLE Speed Sensor Module: BRC01-RS485, BRC01-RS232 [2024-12-08]  */
    bool BRC01_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    bool BRC01_getData(float &speed, float &rpm, int &batt, char *mac, bool &dir);

    /* Inverter ATESS ModbusRTU for Read parameter */
    bool ATESS_R717_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    float ATESS_Power_PV_kW(uint8_t id);
    float ATESS_Power_bat_kW(uint8_t id);
    float ATESS_SOC(uint8_t id);
    float ATESS_ActivePower_Grid_kW(uint8_t id);
    float ATESS_ActivePower_Load_kW(uint8_t id);
    float ATESS_Energy_PVToday_kWh(uint8_t id);
    float ATESS_Energy_BatChargeToday_kWh(uint8_t id);
    float ATESS_Energy_BatDischargeToday_kWh(uint8_t id);
    float ATESS_Energy_GridOutToday_kWh(uint8_t id);
    float ATESS_Energy_GridInToday_kWh(uint8_t id);
    float ATESS_Energy_LoadToday_kWh(uint8_t id);

    /* ModbusRTU Relay Module */
    bool RelayModusRTU_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
    bool RelayModusRTU_Control(uint8_t id = 1, uint8_t channel = 1, bool state = true);
    bool RelayModusRTU_Status(uint8_t id = 1, uint8_t channel = 1);

    /* TF-Luna ToF LiDAR Module - 8 meters Distance Sensor */
    bool TFLiDAR_begin(uint8_t rx = RXD3, uint8_t tx = TXD3);
    int TFLiDAR_getData();
    int TFLiDAR_getData(int &strength, float &temprature);
    bool TFLiDAR_getData(int &distance);
    bool TFLiDAR_getData(int &distance, int &strength);
    bool TFLiDAR_getData(int &distance, int &strength, float &temprature);
};
#endif