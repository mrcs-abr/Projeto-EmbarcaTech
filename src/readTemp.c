#include "../include/readTemp.h"

int convert(uint8_t pin)
{
    writeByte(pin, 0x44);
    int i;
    for (i = 0; i < 500; i++)
    {
        sleep_ms(10);
        if (readBit(pin) == 1)
            break;
    }
    return i;
}

uint8_t crc8(uint8_t *data, uint8_t len)
{
    uint8_t i;
    uint8_t j;
    uint8_t temp;
    uint8_t databyte;
    uint8_t crc = 0;
    for (i = 0; i < len; i++)
    {
        databyte = data[i];
        for (j = 0; j < 8; j++)
        {
            temp = (crc ^ databyte) & 0x01;
            crc >>= 1;
            if (temp)
                crc ^= 0x8C;
            databyte >>= 1;
        }
    }
    return crc;
}
float getTemperature(uint8_t pin)
{
    if (presence(pin) == 1)
        return -1000;
    writeByte(pin, 0xCC);
    if (convert(pin) == 500)
        return -3000;
    presence(pin);
    writeByte(pin, 0xCC);
    writeByte(pin, 0xBE);
    int i;
    uint8_t data[9];
    for (i = 0; i < 9; i++)
    {
        data[i] = readByte(pin);
    }
    uint8_t crc = crc8(data, 9);
    if (crc != 0)
        return -2000;
    int t1 = data[0];
    int t2 = data[1];
    int16_t temp1 = (t2 << 8 | t1);
    float temp = (float)temp1 / 16;
    return temp;
}