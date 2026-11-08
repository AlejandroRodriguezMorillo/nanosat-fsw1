#include "crc16.h"

#define CRC16_POLY 0x1021u
#define CRC16_INIT 0xFFFFu

uint16_t crc16_ccitt(const uint8_t *data, size_t len)
{
    uint16_t crc = CRC16_INIT;
    size_t i;
    int bit;

    for (i = 0; i < len; i++) {
        crc ^= (uint16_t)((uint16_t)data[i] << 8);

        for (bit = 0; bit < 8; bit++) {
               if(crc & 0x8000u) {
                crc = (uint16_t)((crc << 1) ^ CRC16_POLY); 
               } else {
                crc = (uint16_t) (crc <<1);
               }
        }
    }

    return crc;
}
