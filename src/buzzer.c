#include "../include/buzzer.h"

#define BUZZER_PIN 21
#define BUZZER_FREQUENCY 100 // hz

void setup_buzzer()
{
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    pwm_init_buzzer(BUZZER_PIN);
}

void pwm_init_buzzer(uint pin)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096));
    pwm_init(slice_num, &config, true);

    pwm_set_gpio_level(pin, 0);
}

void beep(uint duration_ms)
{
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    pwm_set_gpio_level(BUZZER_PIN, 2048);

    sleep_ms(duration_ms);

    pwm_set_gpio_level(BUZZER_PIN, 0);

    sleep_ms(100);
}