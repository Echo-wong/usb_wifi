#ifndef _MESSAGE_HANDLE_H_
#define _MESSAGE_HANDLE_H_
#include "message.h"

extern void message_sys_init(void);
extern void message_send(uint32_t src_id, uint32_t dst_id, uint32_t msg_id, uint8_t *ex_data, int ex_data_len);
extern void message_bulid(MESSAGE *message, uint32_t src_id, uint32_t dst_id, uint32_t msg_id, uint8_t *ex_data, int ex_data_len);
extern void message_free(MESSAGE *msg);
#endif