#ifndef _MODULES_H_
#define _MODULES_H_
#include "cctypes.h"
#include "message.h"

typedef void (*MESSAGE_HANDLE)(MESSAGE *msg);
extern void modules_manage_init(void);
extern int modules_reg(uint32_t id, MESSAGE_HANDLE handle);
extern void message_handle(MESSAGE *msg);
#endif