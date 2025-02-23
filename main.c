#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "include/readTemp.h"
#include "include/ssd1306Lib/ssd1306.h"
#include "include/leds.h"
#include "include/buzzer.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;
const uint8_t sensor_temp_pin = 16;

int main()
{
    stdio_init_all();

    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init();

    setup_buzzer();

    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

restart:
    char *text[] = {
        "   Tanque 01  ",
        "  Temperatura ",
    };

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 15;
    }

    gpio_init(sensor_temp_pin);

    float sens_temp;
    char msg_temp[18];

    while (1)
    {
        do
        {
            sens_temp = getTemperature(sensor_temp_pin);
        } while (sens_temp < -999);
        printf("%f\r\n", sens_temp);

        sprintf(msg_temp, "   %.1f .C", sens_temp);
        ssd1306_draw_string(ssd, 12, 16, msg_temp);
        render_on_display(ssd, &frame_area);

        if (sens_temp < 28)
        {
            leds_setup(true, false);
            sleep_ms(50);
            leds_setup(false, false);
            beep(500);
        }
        else
        {
            leds_setup(false, true);
        }

        sleep_ms(500);
    };

    return 0;
}