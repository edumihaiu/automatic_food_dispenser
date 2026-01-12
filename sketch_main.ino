#include "Arduino.h"
#include "inc/HX711_driver.h"
#include "inc/RTC_module.h"


HX711_t cantar;
void setup() {
  // put your setup code here, to run once:
  HX711_init(&cantar, -961.672f);
  RTC_init();
  //RTC_setTime(26, 1, 13, 0, 2, 0); // Set time to Jan 12, 2026, 11:31:00
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("atentie tare");
  delay(1000);
  HX711_tare(&cantar);
  Serial.println("tare done");
  while(1) {
  Serial.println(HX711_get_weight(&cantar));
  RTC_printTime();
  delay(1000);}
}
