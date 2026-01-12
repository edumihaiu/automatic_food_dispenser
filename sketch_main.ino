#include "Arduino.h"
#include "inc/HX711_driver.h"

//PINS
#define HX711_DT 2
#define HX711_SCLK 3

HX711_t cantar;
void setup() {
  // put your setup code here, to run once:
  HX711_init(&cantar, HX711_DT, HX711_SCLK);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  HX711_set_scale(&cantar, -1000.542f);
  Serial.println("atentie tare");
  delay(1000);
  HX711_tare(&cantar);
  Serial.println("tare done");
  while(1)
  Serial.println(HX711_get_weight(&cantar));
}
