
#ifndef FSM_H
#define FSM_H

typedef enum {
    STATE_BOOT,
    STATE_DETECTION,
    STATE_NOMINAL,
    STATE_SAFE
} fsm_state_t;

typedef enum {
    EVENT_BOOT_DONE,
    EVENT_CHECKS_PASSED,
    EVENT_CHECKS_FAILED,
    EVENT_ERROR,
    EVENT_RECOVERED
} fsm_event_t;

typedef struct {
    fsm_state_t state;
} fsm_t;

void fsm_init(fsm_t *fsm);
fsm_state_t fsm_update(fsm_t *fsm, fsm_event_t event);
const char *fsm_state_name(fsm_state_t state);

#endif
