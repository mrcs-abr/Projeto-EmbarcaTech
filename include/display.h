#ifndef DISPLAY_H
#define DISPLAY_H
#include "ssd1306Lib/ssd1306.h"
#include "hardware/i2c.h"
#include <string.h>

void setup_display();
void msg_temp_value(float temp_sens);
void msg_state_temp(const char *msg_state_temp);

#endif