/***********************************************************************
 * File         :     tiny32_v3_Lib.h
 * Description  :     Library for Hardware config and function for tiny32_v3 module
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     23 Nov 2021
 * Revision     :     1.0
 * Rev1.0       :     Original
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@innovation.co.th
 * TEL          :     089-140-7205
 ***********************************************************************/

#include "Arduino.h"

/**************************************/
/*           GPIO define              */
/**************************************/
#define SW1     34
#define SW2     35
#define RELAY   25
#define LED_IO4  4
#define LED_IO12  12
#define SLID_SW 36
#define BUZZER  13
#define RXD2    16
#define TXD2    17

static const uint8_t daysInMonth [] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 };


 /***********************************************************************
 * FUNCTION:    TickBlueLED_blink
 * DESCRIPTION: ON-OFF Red LED
 * PARAMETERS:  bool state
 * RETURNED:    nothing
 ***********************************************************************/
void TickBlueLED_blink(void){
    bool _state = digitalRead(LED_IO4);
    digitalWrite(LED_IO4, !_state);
}

 /***********************************************************************
 * FUNCTION:    TickRedLED_blink
 * DESCRIPTION: ON-OFF Red LED
 * PARAMETERS:  bool state
 * RETURNED:    nothing
 ***********************************************************************/
void TickRedLED_blink(void){
    bool _state = digitalRead(LED_IO12);
    digitalWrite(LED_IO12, !_state);
}



 /***********************************************************************
 * FUNCTION:    void TickBuildinLED_blink(void){
 * DESCRIPTION: ON-OFF Buildin LED
 * PARAMETERS:  bool state
 * RETURNED:    nothing
 ***********************************************************************/
void TickBuildinLED_blink(void){
        bool _state = digitalRead(BUILTIN_LED);
        digitalWrite(BUILTIN_LED, !_state);
}