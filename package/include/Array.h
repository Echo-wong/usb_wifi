/******************************************************************************
* Copyright 2010-2020 GVS Co.
* FileName: 	 array.h 
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
#ifndef	 _ARRAYFUN_H
#define	 _ARRAYFUN_H
/*------------------------------- Includes ----------------------------------*/
#include"l_StdType.h"
#include"l_Sys.h"
/*----------------------------- Global Defines ------------------------------*/
#define ARRAY_ARG_SIZE 	128	
//初始化一个变量数值
#define ArgInit(arg) (arg.argc = 0)
/*----------------------------- Global Typedefs -----------------------------*/
typedef struct
{
    UINT8 argv[ARRAY_ARG_SIZE];
    UINT32 argc;
}ARRAY_ARG;
/*----------------------------- External Variables --------------------------*/
/*------------------------ Global Function Prototypes -----------------------*/
/** 
* @brief 搜索指定字节变量在数组中的位置
* @param a    被搜索数组
* @param len  数组长度
* @param b    指定字节
*
* @return 指定字节变量在数组中的位置
* @note 
*/
INT32 ArraySearchByte(UINT8* a,UINT32 len,UINT8 b);
/** 
* @brief 比较两个数组
* @param a1    数组1
* @param a2    数组2
* @param len  数组长度
*
* @return 
*        -<em>0</em> 一致
*        -<em>!0</em> 不一致
* @note 
*/
INT32 ArrayCmp(UINT8 *a1,UINT8 *a2,UINT32 len);
/** 
* @brief 将一个变量打包进变量数组
* @param arg   变量数组指针
* @param argv  变量
* @param argvSize  变量大小
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 不成功
* @note 
*/
INT32 ArgPack(ARRAY_ARG *arg,void *argv,UINT32 argvSize);
/** 
* @brief 将一个变量从变量数组取出
* @param arg   变量数组指针
* @param argv  变量
* @param argvSize  变量大小
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 不成功
* @note 
*/
void ArgGet(void **arg,void *argv,UINT32 argvSize);

#endif /*_ARRAYFUN_H*/

