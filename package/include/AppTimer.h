/******************************************************************************
* Copyright 2010-2020 GVS Co.
* FileName: 	 AppTimer.h
* Desc:
*
*
* Author: 	 Chen li
* Date: 	 2016/01/18
* Notes:
*
* -----------------------------------------------------------------
* Histroy: v1.0   2016/01/18, Chen li create this file
*
******************************************************************************/
#ifndef	 _APPTIMER_H
#define	 _APPTIMER_H
/*------------------------------- Includes ----------------------------------*/
#include"l_Sys.h"
#include"Array.h"
/*----------------------------- Global Defines ------------------------------*/
#define APP_TIMER_COUNT	64
#define AppTimerCounterPrintfTime(name) _AppTimerCounterPrintfTime(name,__LINE__)
/*----------------------------- Global Typedefs -----------------------------*/
typedef void* APP_TIMER_HANDLE;
typedef TIME_TICK_T APP_TIMER_COUNT_T;
typedef void(*TIMER_DEAL_FUN)(APP_TIMER_HANDLE handle, void *argv,UINT32 argc);		//定时器处理函数

typedef enum
{
	APP_TIMER_TYPE_HARDWARE,
	APP_TIMER_TYPE_THREAD,
}APP_TIMER_TYPE;

/*----------------------------- External Variables --------------------------*/
/*------------------------ Global Function Prototypes -----------------------*/
/** 
* @brief 初始化APP定时器
* @param type    定时器类型 APP_TIMER_TYPE_HARDWARE:硬件定时器模式 APP_TIMER_TYPE_THREAD:线程计时模式
*
* @return 无
* @note 
*/
extern void AppTimerInit(APP_TIMER_TYPE type);
/** 
* @brief 注册一个APP定时器
* @param func    回调函数
* @param arg     回调函数参数
* @param ms      定时时长(毫秒)
* @param life    定时器生命周期
*
* @return 返回说明
*        -<em>!NULL</em> 定时器句柄
*        -<em>NULL</em> 注册失败
* @note 定时器使用完后必需调用AppTimerDestroy销毁，否则会存在内存泄露
*/
extern APP_TIMER_HANDLE AppTimerRegister(TIMER_DEAL_FUN func, ARRAY_ARG *arg, APP_TIMER_COUNT_T ms, UINT32 life);
/** 
* @brief 销毁一个APP定时器
* @param handle    定时器句柄指针
*
* @return 返回说明
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern INT32 AppTimerDestroy(APP_TIMER_HANDLE *handle);
/** 
* @brief 开始一个APP定时器
* @param handle    定时器句柄
*
* @return 返回说明
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern INT32 AppTimerStart(APP_TIMER_HANDLE handle);
/** 
* @brief 暂停一个APP定时器
* @param handle    定时器句柄
*
* @return 返回说明
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern INT32 AppTimerStop(APP_TIMER_HANDLE handle);
/** 
* @brief 获取一个APP定时器生命周期
* @param handle    定时器句柄
* @param pOutLife   生命周期返回值
*
* @return 返回说明
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern INT32 AppTimerGetLife(APP_TIMER_HANDLE handle, UINT32 *pOutLife);
/** 
* @brief 获取一个APP定时器运行状态
* @param handle    定时器句柄
*
* @return 返回说明
*        -<em>!0</em> 定时器正在运行
*        -<em>0</em> 定时器未运行或不存在
* @note 
*/
extern INT32 AppTimerGetState(APP_TIMER_HANDLE handle);
/** 
* @brief 设置一个APP定时器生命周期
* @param handle    定时器句柄
* @param life   生命周期
*
* @return 返回说明
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern INT32 AppTimerSetLife(APP_TIMER_HANDLE handle, UINT32 life);
/** 
* @brief 设置一个APP定时器定时时长
* @param handle    定时器句柄
* @param ms   定时时长(毫秒)
*
* @return 返回说明
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern INT32 AppTimerSetTime(APP_TIMER_HANDLE handle, APP_TIMER_COUNT_T ms);
/** 
* @brief 获取一个APP定时器定时时长
* @param handle    定时器句柄
* @param pOutMs   定时时长返回值(毫秒)
*
* @return 返回说明
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern INT32 AppTimerGetTime(APP_TIMER_HANDLE handle, APP_TIMER_COUNT_T *pOutMs);
/** 
* @brief 设置一个APP定时器回调函数
* @param handle    定时器句柄
* @param func   回调函数
* @param arg     回调函数参数
*
* @return 返回说明
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern INT32 AppTimerSetTimerFunction(APP_TIMER_HANDLE handle, TIMER_DEAL_FUN func, ARRAY_ARG *arg);
/** 
* @brief 计算两个TIME_TICK_T的时间间隔
* @param nowTime   当前时间
* @param lastTime  上一个时间点
*
* @return 时间间隔单位为 TIME_TICK_T
* @note 
*/
extern TIME_TICK_T AppTimerGetTickTimeSpan(TIME_TICK_T nowTime, TIME_TICK_T lastTime);
/** 
* @brief 注册并运行或重置一个APP计时器
* @param name    计时器名字
*
* @return 返回说明
*        -<em>!0</em> 成功
*        -<em>0</em> 失败
* @note 计时器最大数量为TIMER_COUNTER_MAX
*/
extern INT32 AppTimerCounterStart(CHAR *name);
/** 
* @brief 销毁一个APP计时器
* @param name    计时器名字
*
* @return 返回说明
*        -<em>!0</em> 成功
*        -<em>0</em> 失败
* @note 
*/
extern void AppTimerCounterDestory(CHAR *name);
/** 
* @brief 获取APP计时器计时时长
* @param name    计时器名字
*
* @return 计时时长 单位为 TIME_TICK_T
* @note 
*/
extern TIME_TICK_T AppTimerCounterGetTime(CHAR *name);
/** 
* @brief 获取APP计时器是否已经注册运行
* @param name    计时器名字
*
* @return 
*        -<em>TRUE</em> 是
*        -<em>FALSE</em> 否
* @note 
*/
extern INT32 AppTimerCounterIsStart(CHAR *name);
/** 
* @brief 打印APP计时器计时时长
* @param name    计时器名字
* @param line    行数
*
* @return 
* @note 
*/
extern void _AppTimerCounterPrintfTime(CHAR *name,INT32 line);
#endif /*_APPTIMER_H*/
