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
//��ʼ��һ��������ֵ
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
* @brief ����ָ���ֽڱ����������е�λ��
* @param a    ����������
* @param len  ���鳤��
* @param b    ָ���ֽ�
*
* @return ָ���ֽڱ����������е�λ��
* @note 
*/
INT32 ArraySearchByte(UINT8* a,UINT32 len,UINT8 b);
/** 
* @brief �Ƚ���������
* @param a1    ����1
* @param a2    ����2
* @param len  ���鳤��
*
* @return 
*        -<em>0</em> һ��
*        -<em>!0</em> ��һ��
* @note 
*/
INT32 ArrayCmp(UINT8 *a1,UINT8 *a2,UINT32 len);
/** 
* @brief ��һ�������������������
* @param arg   ��������ָ��
* @param argv  ����
* @param argvSize  ������С
*
* @return 
*        -<em>0</em> �ɹ�
*        -<em>!0</em> ���ɹ�
* @note 
*/
INT32 ArgPack(ARRAY_ARG *arg,void *argv,UINT32 argvSize);
/** 
* @brief ��һ�������ӱ�������ȡ��
* @param arg   ��������ָ��
* @param argv  ����
* @param argvSize  ������С
*
* @return 
*        -<em>0</em> �ɹ�
*        -<em>!0</em> ���ɹ�
* @note 
*/
void ArgGet(void **arg,void *argv,UINT32 argvSize);

#endif /*_ARRAYFUN_H*/

