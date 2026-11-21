
#ifndef SCHED_H
#define SCHED_H

#include <stdint.h>
#include <stddef.h>

typedef void (*task_fn)(void *ctx);

int  sched_add(uint32_t period_ticks, task_fn fn, void *ctx);
void sched_run(uint32_t now_ticks);
void sched_reset(void);

#endif