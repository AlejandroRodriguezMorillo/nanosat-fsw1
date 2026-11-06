#include "fsm.h"

void fsm_init(fsm_t *fsm) {
    fsm -> state = STATE_BOOT;
}

fsm_state_t fsm_update(fsm_t *fsm, fsm_event_t event) {
    switch (fsm -> state)
    {
    case STATE_BOOT:
        if (event == EVENT_BOOT_DONE) {
            fsm -> state = STATE_DETECTION;
        }
        break;
    case STATE_DETECTION:
        if (event == EVENT_CHECKS_PASSED) {
            fsm->state = STATE_NOMINAL;
        }
        else if (event == EVENT_CHECKS_FAILED) {
            fsm -> state = STATE_SAFE;
        }
        break;
    case STATE_NOMINAL:
        if(event == EVENT_ERROR) {
            fsm->state = STATE_SAFE;
        }
        break;
    case STATE_SAFE:
        if(event == EVENT_RECOVERED) {
            fsm->state = STATE_DETECTION;
        }
        break;
    default:
        break;
    }
    return fsm-> state;
}

const char *fsm_state_name(fsm_state_t state){
    const char *res = "UNKNOWN";
    
    switch (state)
    {
    case STATE_BOOT:
        res = "BOOT";
        break;
    case STATE_DETECTION:
        res = "DETECTION";
        break;
    case STATE_NOMINAL:
        res = "NOMINAL";
        break;
    case STATE_SAFE:
        res = "SAFE";
        break;
    default:
        break;
    }
    return res;
} 
