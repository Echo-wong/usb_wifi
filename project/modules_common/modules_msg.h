#ifndef _MODULES_MSG_H
#define _MODULES_MSG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "cclib.h"
#include "modules_id.h"
#include "message_id.h"

/** 
* @brief 初始化一个消息服务端
* @param id    模块ID
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 服务端有且只能有一个，目前Environment应用是服务端
*/
extern int modules_msg_init_server(uint32_t id);
/** 
* @brief 初始化一个消息客户端
* @param id    模块ID
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern int modules_msg_init_client(uint32_t id);
/** 
* @brief 发送一个消息
* @param src_id    发送模块ID
* @param dst_id    接收模块ID
* @param msg_id    消息类型
* @param ex_data    消息附带内容
* @param ex_data_len   消息附带内容大小
*
* @note 
*/
extern void msg_send(uint32_t src_id, uint32_t dst_id, uint32_t msg_id, void *ex_data, int ex_data_len);

#ifdef __cplusplus
}
#endif
#endif
