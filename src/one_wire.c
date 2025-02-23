#include "../include/one_wire.h"

int presence(uint8_t pin)
{
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 1);
    sleep_ms(1);
    gpio_put(pin, 0);
    sleep_us(480);
    gpio_set_dir(pin, GPIO_IN);
    sleep_us(70);
    int b = gpio_get(pin);
    sleep_us(410);
    return b;
}

void writeBit(uint8_t pin, int b)
{
    int delay1, delay2;
    if (b == 1)
    {
        delay1 = 6;
        delay2 = 64;
    }
    else
    {
        delay1 = 60;
        delay2 = 10;
    }
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 0);
    sleep_us(delay1);
    gpio_set_dir(pin, GPIO_IN);
    sleep_us(delay2);
}

void writeByte(uint8_t pin, int byte)
{
    for (int i = 0; i < 8; i++)
    {
        if (byte & 1)
        {
            writeBit(pin, 1);
        }
        else
        {
            writeBit(pin, 0);
        }
        byte = byte >> 1;
    }
}

uint8_t readBit(uint8_t pin)
{
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 0);
    sleep_us(8);
    gpio_set_dir(pin, GPIO_IN);
    sleep_us(2);
    uint8_t b = gpio_get(pin);
    sleep_us(60);
    return b;
}
int readByte(uint8_t pin)
{
    int byte = 0;
    int i;
    for (i = 0; i < 8; i++)
    {
        byte = byte | readBit(pin) << i;
    };
    return byte;
}
