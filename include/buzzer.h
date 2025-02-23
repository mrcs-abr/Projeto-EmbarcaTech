#ifndef BUZZER_H
#define BUZZER_H

#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

void pwm_init_buzzer(uint pin);
void beep(uint duration_ms);
void setup_buzzer();

#endif