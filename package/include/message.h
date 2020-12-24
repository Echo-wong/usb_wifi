#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include "cctypes.h"
#include "message.h"

typedef struct
{
    uint32_t msg_id;
    uint32_t sender_id;
    uint32_t receiver_id;
    void *tag;
    int tag_size;
} MESSAGE;

#define BROADCAST_MESSAGE 0xFFFFFFFF

#endif