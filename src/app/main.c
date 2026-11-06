
#include <stdio.h>
#include "version.h"
#include "fsm.h"

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


    return 0;
}
