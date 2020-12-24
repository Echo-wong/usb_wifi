/******************************************************************************
* Copyright 2010-2020 GVS Co.
* FileName: 	 Queue.h 
* Desc:
* 
* 
* Author: 	 Chen li
* Date: 	 2016/01/19
* Notes: 
* 
* -----------------------------------------------------------------
* Histroy: v1.0   2016/01/19, Chen li create this file
* 
******************************************************************************/
#ifndef	 _QUEUE_H
#define	 _QUEUE_H
/*------------------------------- Includes ----------------------------------*/
#include"l_Sys.h"
#include <stdlib.h>
#include <pthread.h>
/*----------------------------- Global Typedefs -----------------------------*/

typedef enum 
{
    LIST_TYPE_NORMAL,
    LIST_TYPE_FIXED_LENGTH,
}LIST_TYPE;

typedef struct _LIST_ITEM
{
    struct _LIST_ITEM *pre;
    UINT8 *data;
    UINT32 dataLen;
    struct _LIST_ITEM *next;
    
}LIST_ITEM;

typedef struct
{
    UINT32 count;
    LIST_ITEM *head;
    LIST_ITEM *tail;
    LIST_TYPE type;
    UINT32 maxCount;
    UINT8 *buff;
    UINT32 dataLen;
    LIST_ITEM *lastItem;
    UINT32 lastPos;
    THREAD_LOCK lock;
}LIST;


typedef void (*ListContentPrintf)(UINT8* content);
typedef BOOL (*ListCmp)(UINT8 *data,void *para);
/*----------------------------- Global Defines ------------------------------*/
#define ListAdd(pList,member) ListAddArray(pList,(UINT8*)&(member),sizeof(member))
#define ListGet(pList,index,type) ((type*)ListGetArray(pList,index))
#define ListSearch(pList,Cmp,para,type) (type*)ListSearchArray(pList,Cmp,para)
/*----------------------------- External Variables --------------------------*/
/*------------------------ Global Function Prototypes -----------------------*/
LIST *NewList(void);
LIST *NewListFixedLength(UINT32 maxCount,UINT32 dataLen);
LIST *NewListS(void);
LIST *NewListFixedLengthS(UINT32 maxCount,UINT32 dataLen);
void FreeList(LIST *pList);
INT32 ListAddArray(LIST *pList,UINT8* data,UINT32 dataLen);
UINT8 *ListGetArray(LIST *pList,UINT32 index);
UINT8 *ListSearchArray(LIST *pList,ListCmp Cmp,void *para);
INT32 ListDelete(LIST *pList,UINT32 index);
INT32 ListDeleteItem(LIST *pList,void *delItem);
void ListClear(LIST *pList);
void ListPrintf(LIST *pList,ListContentPrintf ContentPrintf);
LIST *ListClone(LIST *src);
#endif /*_QUEUE_H*/

