/***********************************************************************
 * Project      :     Example_BuzzerTest
 * Description  :     Test Buzzer on tiny32_v3 board
 * Hardware     :     tiny32_v3         
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     19/02/2022
 * Revision     :     1.0
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-308-3299
 ***********************************************************************/
#include <tiny32_v3.h>

tiny32_v3 mcu; //define object

void setup() {
  Serial.begin(115200);
  Serial.printf("\r\n**** Example_BuzzerTest ****\r\n");
  mcu.library_version();
}

void loop() {
  
  /**** one beep ****/
  Serial.printf("one beep\r\n");
  mcu.buzzer_beep(1);
  vTaskDelay(1000);

  /**** two beep ****/
  Serial.printf("two beep\r\n");
  mcu.buzzer_beep(2);
  vTaskDelay(1000);

  /**** three beep ****/
  Serial.printf("three beep\r\n");
  mcu.buzzer_beep(3);
  vTaskDelay(1000);

  /**** four beep ****/
  Serial.printf("four beep\r\n");
  mcu.buzzer_beep(4);
  vTaskDelay(1000);
  
}
