#include "../inc/misc.h"
#include <avr/io.h>


#define INPUT 0
#define OUTPUT 1

uint8_t my_digitalRead(uint8_t pin)
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

void my_pinMode(uint8_t pin, uint8_t mode)
{
    if (pin <= 7) {
        if (mode == INPUT) {
            DDRD &= ~(1 << pin);
        } else {
            DDRD |= (1 << pin);
        }
    } else if (pin <= 13) {
        if (mode == INPUT) {
            DDRB &= ~(1 << (pin - 8));
        } else {
            DDRB |= (1 << (pin - 8));
        }
    } else if (pin <= 18) {
        if (mode == INPUT) {
            DDRC &= ~(1 << (pin - 14));
        } else {
            DDRC |= (1 << (pin - 14));
        }
    }
}

void my_digitalWrite(uint8_t pin, uint8_t val) {
    if (pin <= 7) {
        if (val) PORTD |= (1 << pin); else PORTD &= ~(1 << pin);
    } else if (pin <= 13) {
        if (val) PORTB |= (1 << (pin - 8)); else PORTB &= ~(1 << (pin - 8));
    } else if (pin <= 18) {
        if (val) PORTC |= (1 << (pin - 14)); else PORTC &= ~(1 << (pin - 14));
    }
}