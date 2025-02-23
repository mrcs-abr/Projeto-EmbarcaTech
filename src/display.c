#include "../include/display.h"
#include <string.h>
#include <stdio.h>

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

uint8_t ssd[ssd1306_buffer_length];
struct render_area frame_area;

void setup_display()
{
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init();

    frame_area.start_column = 0;
    frame_area.end_column = ssd1306_width - 1;
    frame_area.start_page = 0;
    frame_area.end_page = ssd1306_n_pages - 1;

    calculate_render_area_buffer_length(&frame_area);

    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    char *display_layout[] = {
        "   Tanque 01  ",
        "  Temperatura ",
    };

    int y = 0;
    for (uint i = 0; i < count_of(display_layout); i++)
    {
        ssd1306_draw_string(ssd, 5, y, display_layout[i]);
        y += 15;
    }
}

void msg_temp_value(float temp_sens)
{
    char msg_temp[18];
    sprintf(msg_temp, "   %.1f .C", temp_sens);
    ssd1306_draw_string(ssd, 12, 24, msg_temp);
    render_on_display(ssd, &frame_area);
}

void msg_state_temp(const char *msg_state_temp)
{
    char msg_low_temp[13];
    sprintf(msg_low_temp, msg_state_temp);
    ssd1306_draw_string(ssd, 12, 40, msg_low_temp);
    render_on_display(ssd, &frame_area);
}