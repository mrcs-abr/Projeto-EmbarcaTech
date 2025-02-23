#ifndef LEDS_H
#define LEDS_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

void leds_setup(bool RED_VALUE, bool GREEN_VALUE);

#endif