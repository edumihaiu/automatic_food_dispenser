#include "Arduino.h"
#include "inc/HX711_driver.h"
#include "inc/RTC_module.h"
#include "inc/Stepper_module.h"


HX711_t cantar;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HX711_init(&cantar, -961.672f);
  RTC_init();
  RTC_setTime(26, 1, 13, 1, 12, 55); // Set time to Jan 12, 2026, 11:31:00
  Stepper_init();

  Serial.println("setup done");
}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned long lastCheck = 0;
    
  if (millis() - lastCheck >= 1000) {
      lastCheck = millis();

      if (RTC_isMealTime(1, 13)) {
        Serial.println("dispensing");
        int res = Stepper_dispense(50.0f); // dispense 50 grams
        if (res == 1) {
          Serial.println("sucessful");
        } else {
          Serial.println("failed");
        }
      } else {
        Serial.println("not meal time yet");
        Serial.print("Current time: ");
        RTC_printTime();
        Serial.print("  ||  weight: ");
        Serial.println(HX711_get_weight(&cantar));
      }
  }


  //Serial.println("atentie tare");
  //delay(1000);
  //HX711_tare(&cantar);
  //Serial.println("tare done");
  //while(1) {
  //Serial.println(HX711_get_weight(&cantar));
  //RTC_printTime();
  //delay(1000);}
}
