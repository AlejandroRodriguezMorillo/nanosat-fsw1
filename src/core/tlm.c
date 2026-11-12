
#include "tlm.h"
#include "crc16.h" 

static void put_u16(uint8_t *buf, uint16_t v) {
    buf[0] = (uint8_t)(v >>8);
    buf[1] = (uint8_t)(v & 0xFF);
}

static uint16_t get_u16(const uint8_t *buf) {

    uint16_t res = (uint16_t)((uint16_t)buf[0] << 8 | buf[1]);
    return res;
}

size_t tlm_build(const tlm_snapshot_t *snap, uint8_t *out, size_t out_len)
{
    /* Guarda de seguridad: no escribas fuera del buffer */
    if (snap == NULL || out == NULL || out_len < TLM_FRAME_SIZE) {
        return 0;
    }

    /* Sync marker, byte a byte */
    out[0] = 0x1A;
    out[1] = 0xCF;
    out[2] = 0xFC;
    out[3] = 0x1D;

    out[4] = TLM_VERSION;
    out[5] = (uint8_t)snap->state;

    put_u16(&out[6],  snap->timestamp);
    put_u16(&out[8],  (uint16_t)snap->temperature_c10);
    put_u16(&out[10], snap->battery_mv);

    uint16_t crc = crc16_ccitt(out, 12);
    put_u16(&out[12], crc);
    return TLM_FRAME_SIZE;
}

int tlm_verify(const uint8_t *frame, size_t len)
{
    /* TODO:
       1. si frame es NULL o len != TLM_FRAME_SIZE → return 0
       2. comprueba que los 4 primeros bytes son el sync marker
       3. calcula el CRC de los 12 primeros bytes
       4. compáralo con get_u16(&frame[12]) → return 1 si coinciden, 0 si no
    */
   int res = 0;
    if(frame==NULL || len != TLM_FRAME_SIZE) {
            return 0;
        }
        if(frame[0] == 0x1A && frame[1] == 0xCF && frame[2] == 0xFC &&
        frame[3] == 0x1D) {
            uint16_t crc_calc = crc16_ccitt(frame, 12);
            uint16_t crc_recv = get_u16(&frame[12]);
            if(crc_calc == crc_recv) {
                res =  1;
            }
    }
    

    return res;
}