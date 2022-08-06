/***********************************************************************
 * Project      :     Example_OTA
 * Description  :     Update firmware for tiny32 via OTA (Over-the-Air)
 * Hardware     :     tiny32_v3
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     06/08/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-308-3299
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <WiFi.h>
#include "otaUpdate.h"

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;


/**************************************/
/*           Wifi parameter           */
/**************************************/
const char *ssid = "xxxxxxxx";
const char *password = "xxxxxxxx";


/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    Serial.printf("**** Example_OTA ****\r\n");
    mcu.library_version();

    Serial.print("Info: Connecting Wi-Fi....");
    uint8_t _error_cnt = 0; // variable for wifi connection count
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");

        if (_error_cnt++ > 60) // more than 30 second if can't connect to wifi, system will restart
        {
            Serial.printf("Error: Can't connect to wifi\r\n");
            ESP.restart();
            mcu.buzzer_beep(3);
        }
    }

    Serial.println("Connected \r\n");
    mcu.TickBlueLED(1.0); // Blue LED show blink 1 second
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    otaUpdateFunction(); //*call OTA function
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
    /*** OTA function ***/ 
    serverOTA.handleClient();     
    vTaskDelay(1000);
}
