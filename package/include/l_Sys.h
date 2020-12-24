/******************************************************************************
* Copyright 2010-2020 GVS Co.
* FileName: 	 l_Sys.h 
* Desc:
* 
* 
* Author: 	 Chen li
* Date: 	 2017/10/24
* Notes: 
* 
* -----------------------------------------------------------------
* Histroy: v1.0   2017/10/24, Chen li create this file
* 
******************************************************************************/
#ifndef	 _LINUX_SYS_H
#define	 _LINUX_SYS_H
/*------------------------------- Includes ----------------------------------*/
#include"l_StdType.h"
#include<semaphore.h>  
#include<pthread.h>
#include<string.h>
/*----------------------------- Global Defines ------------------------------*/
#if MALLOC_TRACE
#define Malloc(size) MallocTrace(size,__FILE__,__LINE__)
#define Free(p) FreeTrace(p,__FILE__,__LINE__)
#define KMalloc(size) MallocTrace(size,__FILE__,__LINE__)
#else
#define Malloc malloc
#define Free free
#define KMalloc malloc
#endif

#define BASE_TIMER_TICK 50
#define MsToTimerTick(ms) (ms/BASE_TIMER_TICK)
#define TimerTickToMs(tick) (tick*BASE_TIMER_TICK)

#define Memcpy memcpy
#define Strcpy strcpy
#define Strcmp strcmp
#define Printf printf
/*----------------------------- Global Typedefs -----------------------------*/
typedef sem_t * SEM;
typedef pthread_mutex_t * THREAD_LOCK;
typedef pthread_t THREAD;
typedef enum
{
    THREAD_PARAM_START,
    THREAD_PARAM_SUSPENDED,
}THREAD_PARAM_STATUS;

typedef struct
{
    INT32 policy;
    INT32 stackSize;
    void *arg;
    THREAD_PARAM_STATUS status;
}THREAD_PARAM;

//typedef UINT64 TIME_TICK_T;
/*----------------------------- External Variables --------------------------*/
/*------------------------ Global Function Prototypes -----------------------*/
#if MALLOC_TRACE
extern void *MallocTrace(UINT32 size,CHAR *file,INT32 line);
extern void FreeTrace(void *buff, CHAR *file, INT32 line);
#endif

extern SEM NewSem(INT32 val);
extern void FreeSem(SEM sem);
extern INT32 SemPost(SEM sem);
extern INT32 SemWait(SEM sem);
extern THREAD_LOCK NewThreadLock(void);
extern INT32 FreeThreadLock(THREAD_LOCK lock);
extern INT32 ThreadLock(THREAD_LOCK lock);
extern INT32 ThreadUnlock(THREAD_LOCK lock);
extern THREAD ThreadCreate(void (*start)(void),THREAD_PARAM *para);
extern void MSleep(UINT32 ms);
extern INT32 GetSleepPeriod(void);
extern TIME_TICK_T GetSysMs(void);
extern INT32 BaseTimerFunctionSet(void(*Fun)(void));
#endif /*_LINUX_SYS_H*/

