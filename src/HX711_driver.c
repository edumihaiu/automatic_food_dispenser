#include "HX711_driver.h"
#include "misc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void HX711_init(HX711_t* sensor, uint8_t dt, uint8_t sclk)
{
    sensor->dt_pin = dt;
    sensor->sclk_pin = sclk;
    sensor->offset = 0;
    sensor->scale = 1.0f;
}


int32_t HX711_readRaw(HX711_t* sensor)
{
    	while(my_digitalRead(sensor->dt_pin)); // wait until DOUT is LOW

	int32_t value = 0;
	uint8_t i;
	cli(); // no interrupts
	for (i = 0; i < 24; ++i) {
		PORTD |= (1 << sensor->sclk_pin); // write HIGH SCLK

		value = value << 1;
		value |= my_digitalRead(sensor->dt_pin);

		PORTD &= ~(1 << sensor->sclk_pin); // write LOW SCLK
	}

	if (value & 0x800000L) {
		// check if MSB is HIGH; if it is -> negative
		// if it is fill from 31 to 24 with HIGH
		value |= 0xFF000000L;
	}

	PORTD |= (1 << sensor->sclk_pin); // set channel A 128 rate
	PORTD &= ~(1 << sensor->sclk_pin);
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