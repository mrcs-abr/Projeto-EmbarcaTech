#ifndef READTEMP_H
#define READTEMP_H

#include "one_wire.h"

int convert(uint8_t pin);
uint8_t crc8(uint8_t *data, uint8_t len);
float getTemperature(uint8_t pin);

#endif // READTEMP_H