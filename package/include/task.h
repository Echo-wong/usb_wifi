#ifndef _TASK_H_
#define _TASK_H_

#include<pthread.h>
#include <semaphore.h>
#include"cctypes.h"
#include"queue.h"
#include "sys_time.h"

typedef struct _TASK TASK;
typedef struct _TASK_MASTER TASK_MASTER;

struct _TASK
{
    TASK_MASTER *master;
    int is_release;
    int is_finish;
    int is_stop;
    int time_out;
    TIME_COUNTER timer_counter;
    void (*user_task_finish)(TASK *task,int is_fail);
    TASK *next_task;
};



struct _TASK_MASTER
{
    TASK * (*task_new)(TASK_MASTER *master,int task_struct_size,int time_out,...);
    void (*task_release)(TASK_MASTER *master,TASK *task);
    void (*task_start)(TASK_MASTER *master,TASK *task);
    void (*task_stop)(TASK_MASTER *master,TASK *task);
    LIST *task_list;
    pthread_mutex_t lock;
    sem_t task_sem;
    int exit_flag;
    int check_interval;

    void (*user_task_init)(TASK *task,va_list va);
    int (*user_task_run)(TASK *task);
    void (*user_task_deinit)(TASK *task);
} ;


extern void task_sys_init(void);
extern TASK_MASTER *task_master_new(void);
#endif
