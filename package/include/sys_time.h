#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include "cctypes.h"
typedef struct _TIME_COUNTER TIME_COUNTER;

struct _TIME_COUNTER
{
    uint64_t time;
    void (*start)(TIME_COUNTER *counter);
    void (*reset)(TIME_COUNTER *counter);
    uint64_t (*get_interval)(TIME_COUNTER *counter);
} ;

extern uint64_t get_sys_ms(void);
extern void timer_counter_init(TIME_COUNTER *counter);
#endif