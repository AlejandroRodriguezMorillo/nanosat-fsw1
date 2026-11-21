
#include "sched.h"

#define MAX_TASKS 4u

typedef struct {
    uint32_t period;
    uint32_t last_run;
    task_fn  fn;
    void    *ctx;
    int      used;
} task_t;

static task_t tasks[MAX_TASKS];

int sched_add(uint32_t period, task_fn fn, void *ctx)
{
   
    if( period == 0 || fn == NULL ) {
        return -1;
    } 
    for(uint32_t i=0; i < MAX_TASKS; i++){
        if (tasks[i].used == 0) {
            tasks[i].last_run = 0;
            tasks[i].used = 1;
            tasks[i].period = period;
            tasks[i].ctx = ctx;
            tasks[i].fn = fn;
            return (int)i;
        }    
    }
    return -1;
}

void sched_run(uint32_t now) {
    
   for(uint32_t i = 0; i < MAX_TASKS;i++){
        if ( tasks[i].used &&  (now-tasks[i].last_run >= tasks[i].period)) {
            tasks[i].last_run = now;
            tasks[i].fn(tasks[i].ctx);
        }
   }
}

void sched_reset(void)
{
    uint32_t i;
    for (i = 0; i < MAX_TASKS; i++) {
        tasks[i].used = 0;
    }
}