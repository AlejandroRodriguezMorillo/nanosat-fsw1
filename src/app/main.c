
#include <stdio.h>
// #include "version.h"
#include "fsm.h"
#include "crc16.h"
#include "tlm.h"
#include "sched.h"


static void task_telemetry(void *ctx)
{
    (void)ctx;   /* evita el warning de parámetro no usado con -Wextra */
    printf("  [tlm]    telemetria\n");
}

static void task_health(void *ctx)
{
    (void)ctx;
    printf("  [health] comprobando bateria\n");
}

int main(void) {

    fsm_t sat;
    fsm_init(&sat);

    printf("\n[%s]\n", fsm_state_name(sat.state));
    
    fsm_update(&sat, EVENT_BOOT_DONE);
    printf("event: BOOT_DONE -> [%s]\n", fsm_state_name(sat.state));
    
    fsm_update(&sat, EVENT_CHECKS_PASSED);
    printf("event: CHECKS_PASSED -> [%s]\n", fsm_state_name(sat.state));

    fsm_update(&sat,EVENT_ERROR );
    printf("event: ERROR -> [%s]\n", fsm_state_name(sat.state));

    fsm_update(&sat, EVENT_RECOVERED);
    printf("event: RECOVERED -> [%s]\n", fsm_state_name(sat.state));
    // ------------------------------------FIN DE FSM----------------------------------------------------
    printf("------------------------------------FIN DE FSM---------------------------------------------------- \n ");

    const uint8_t test[] = "123456789";
    uint16_t crc = crc16_ccitt(test, sizeof(test) - 1);   /* 9 = longitud sin el '\0' */
    printf("CRC16(\"123456789\") = 0x%04X (esperado: 0x29B1)\n", crc);


    printf("------------------------------------FIN DE CRC16---------------------------------------------------- \n ");

    tlm_snapshot_t snap = {
        .state           = STATE_NOMINAL,
        .timestamp       = 42,
        .temperature_c10 = 253,
        .battery_mv      = 3800
    };
    uint8_t frame[TLM_FRAME_SIZE];
    size_t n = tlm_build(&snap, frame, sizeof(frame));

    printf("frame (%u bytes): ", (unsigned)n);
    for (size_t i = 0; i < n; i++) {
        printf("%02X ", frame[i]);
    }
    printf("\nverify: %s\n", tlm_verify(frame, n) ? "OK" : "BAD");


    
    frame[8] ^= 0x01;   /* corrompe un bit de la temperatura */
    printf("verify tras corromper: %s\n", tlm_verify(frame, n) ? "OK" : "BAD");

    printf("------------------------------------FIN DE TLM---------------------------------------------------- \n ");
    
    printf("\n=== scheduler demo ===\n");
    sched_reset();
    sched_add(3, task_telemetry, NULL);
    sched_add(5, task_health, NULL);

    for (uint32_t t = 1; t <= 15; t++) {
        sched_run(t);
        printf("tick %u\n", t);
    }

    printf("------------------------------------FIN DE SCHED---------------------------------------------------- \n ");


    return 0;
}

