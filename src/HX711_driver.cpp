#include "../inc/HX711_driver.h"
#include "../inc/misc.h"
#include "../inc/pins.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define INPUT 0
#define OUTPUT 1


void HX711_init(HX711_t* sensor, float scale)
{
    sensor->dt_pin = HX711_DT;
    sensor->sclk_pin = HX711_SCLK;
    sensor->offset = 0;
    sensor->scale = 1.0f;

	my_pinMode(sensor->dt_pin, INPUT);
	my_pinMode(sensor->sclk_pin, OUTPUT);

	HX711_set_scale(sensor, scale);
	HX711_tare(sensor);
}


int32_t HX711_readRaw(HX711_t* sensor)
{
    	while(my_digitalRead(sensor->dt_pin)); // wait until DOUT is LOW

	int32_t value = 0;
	uint8_t i;
	cli(); // no interrupts
	for (i = 0; i < 24; ++i) {
		my_digitalWrite(sensor->sclk_pin, 1); // write HIGH SCLK

		value = value << 1;
		value |= my_digitalRead(sensor->dt_pin);

		my_digitalWrite(sensor->sclk_pin, 0); // write LOW SCLK
	}

	if (value & 0x800000L) {
		// check if MSB is HIGH; if it is -> negative
		// if it is fill from 31 to 24 with HIGH
		value |= 0xFF000000L;
	}

	my_digitalWrite(sensor->sclk_pin, 1); // set channel A 128 rate
	my_digitalWrite(sensor->sclk_pin, 0);
	sei(); // interrupts back
	return value;
}

int32_t HX711_readAvg(HX711_t* sensor, uint8_t n)
{
    int64_t sum = 0;
	uint8_t i;
	for (i = 0; i < n; ++i) {
		sum += HX711_readRaw(sensor);
	}
	return (int32_t)(sum / n);
}


void HX711_tare(HX711_t* sensor) {
	sensor->offset = HX711_readAvg(sensor, 10);
}

void HX711_set_scale(HX711_t* sensor, float scale) {
	sensor->scale = scale;
}

float HX711_get_weight(HX711_t* sensor) {
	return (HX711_readAvg(sensor, 10) - sensor->offset) / sensor->scale;
}