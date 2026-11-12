
#ifndef TLM_H
#define TLM_H

#include <stdint.h>
#include <stddef.h>
#include "fsm.h"

#define TLM_SYNC_WORD   0x1ACFFC1Du
#define TLM_VERSION     0x01u
#define TLM_FRAME_SIZE  14u

typedef struct {
    fsm_state_t state;
    uint16_t    timestamp;
    int16_t     temperature_c10;
    uint16_t    battery_mv;
} tlm_snapshot_t;

size_t tlm_build(const tlm_snapshot_t *snap, uint8_t *out, size_t out_len);
int    tlm_verify(const uint8_t *frame, size_t len);

#endif