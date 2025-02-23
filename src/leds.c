#include "../include/leds.h"

const uint8_t GREEN_LED = 11;
const uint8_t RED_LED = 13;

void leds_setup(bool RED_VALUE, bool GREEN_VALUE)
{
    gpio_init(GREEN_LED);
    gpio_init(RED_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_set_dir(RED_LED, GPIO_OUT);

    gpio_put(GREEN_LED, GREEN_VALUE);
    gpio_put(RED_LED, RED_VALUE);
}