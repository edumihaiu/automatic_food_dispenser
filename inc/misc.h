#ifndef MISC_H
#define MISC_H

#include <stdint.h>

uint8_t my_digitalRead(uint8_t pin);
void my_digitalWrite(uint8_t pin, uint8_t val);
void my_pinMode(uint8_t pin, uint8_t mode);

#endif // MISC_H