
#include <stdio.h>
// #include "version.h"
#include "fsm.h"
#include "crc16.h"

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

    const uint8_t test[] = "123456789";
    uint16_t crc = crc16_ccitt(test, sizeof(test) - 1);   /* 9 = longitud sin el '\0' */
    printf("CRC16(\"123456789\") = 0x%04X (esperado: 0x29B1)\n", crc);

    return 0;
}

