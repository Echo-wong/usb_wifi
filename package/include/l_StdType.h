/******************************************************************************
* Copyright 2010-2020 GVS Co.
* FileName: 	 l_StdType.h 
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
#ifndef	 _LINUX_STDTYPE_H
#define	 _LINUX_STDTYPE_H

#include<stdarg.h>
#include<stdint.h>
#include<stdlib.h>

//#define NULL 0

#define FALSE             0
#define TRUE              1

typedef char              BOOL;

typedef char              INT8;


typedef char              CHAR;

typedef unsigned char     UINT8;
typedef unsigned char     UCHAR;

typedef short             SHORT;
typedef unsigned short    USHORT;

typedef short             INT16;
typedef unsigned short    UINT16;

typedef int               INT32;
typedef unsigned int      UINT32;
typedef long long         INT64;
typedef unsigned long long  UINT64;


typedef float             FLOAT;
typedef double            DOUBLE;

typedef uint64_t TIME_TICK_T;

#define VA_LIST va_list
#define VA_START va_start
#define VA_ARG va_arg
#define VA_END va_end

//#define NOP(arg,...)  ;   
#endif /*_LINUX_STDTYPE_H*/

