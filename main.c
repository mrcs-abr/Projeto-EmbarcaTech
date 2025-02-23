#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "include/readTemp.h"
#include "include/leds.h"
#include "include/buzzer.h"
#include "include/alert.h"
#include "include/display.h"

const uint8_t LOWER_TEMP_LIMIT = 28;
const uint8_t HIGHER_TEMP_LIMIT = 30;
const uint8_t TEMP_SENSOR_PIN = 16;

int main()
{
    stdio_init_all();
    setup_display();
    setup_buzzer();
    gpio_init(TEMP_SENSOR_PIN);
    float temp_sens;

    while (1)
    {
        do
        {
            temp_sens = getTemperature(TEMP_SENSOR_PIN);
        } while (temp_sens < -999);
        printf("%f\r\n", temp_sens);

        msg_temp_value(temp_sens);

        if (temp_sens < LOWER_TEMP_LIMIT)
        {
            alert_event();
            msg_state_temp(" temp baixa ");
        }
        else if (temp_sens > HIGHER_TEMP_LIMIT)
        {
            alert_event();
            msg_state_temp(" temp alta  ");
        }
        else
        {
            safe_event();
            msg_state_temp("temp estavel");
        }

        sleep_ms(500);
    };

    return 0;
}