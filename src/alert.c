#include "../include/alert.h"

const uint BEEP_DURATION = 500;

void alert_event()
{
    leds_setup(true, false);
    sleep_ms(50);
    leds_setup(false, false);
    beep(BEEP_DURATION);
}

void safe_event()
{
    leds_setup(false, true);
}
