#ifndef ONE_WIRE_H
#define ONE_WIRE_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

int presence(uint8_t pin);
void writeBit(uint8_t pin, int b);
void writeByte(uint8_t pin, int byte);
uint8_t readBit(uint8_t pin);
int readByte(uint8_t pin);

#endif