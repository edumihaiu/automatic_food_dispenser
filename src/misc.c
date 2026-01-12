#include "misc.h"
#include <avr/io.h>

int my_digitalRead(uint8_t pin)
{
    if (pin <= 7) {
        return (PIND & (1 << pin)) ? 1 : 0;
    } else if (pin <= 13) {
        return (PINB & (1 << (pin - 8))) ? 1 : 0;
    } else if (pin <= 18) {
        return (PINC & (1 << (pin - 14))) ? 1 : 0;
    }
    return 0;
}