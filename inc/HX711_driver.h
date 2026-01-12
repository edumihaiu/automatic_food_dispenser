#ifndef HXX711_DRIVER_H
#define HXX711_DRIVER_H


#include <stdint.h>

typedef struct {
    int32_t offset;
    float scale;
    uint8_t dt_pin;
    uint8_t sclk_pin;
} HX711_t;

void HX711_init(HX711_t* sensor, float scale);
int32_t HX711_readRaw(HX711_t* sensor);
int32_t HX711_readAvg(HX711_t* sensor, uint8_t n);
void HX711_tare(HX711_t* sensor);
void HX711_set_scale(HX711_t* sensor, float scale);
float HX711_get_weight(HX711_t* sensor);

#endif // HXX711_DRIVER_H