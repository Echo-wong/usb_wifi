#ifndef _APP_CONF_H_
#define _APP_CONF_H_
#include "modules_msg.h"

#ifdef __cplusplus
extern "C"
{
#endif
typedef enum
{
    APP_CONF_TYPE_FILE,     //参数存储于配置文件中
    APP_CONF_TYPE_RAM,      //参数存储于RAM中，断电不保存
    APP_CONF_TYPE_FLASH,    //参数存储于FLASH中（未实现）
}APP_CONF_TYPE;

typedef void (*APP_CONF_HANDLE)(char *name,char*val);
/** 
* @brief 配置参数模块初始化
* @param id   模块ID
*/
extern void app_conf_init(uint32_t id);
/** 
* @brief 注册一个字符串类型的配置参数
* @param name    参数名
* @param val    配置参数默认值
* @param handle    参数回调，当参数被更改后该回调会被调用
* @param type    参数存储类型
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern int app_conf_reg_string(char *name,char*val,APP_CONF_HANDLE handle,APP_CONF_TYPE type);
/** 
* @brief 注册一个整型的配置参数
* @param name    参数名
* @param val    配置参数默认值
* @param handle    参数回调，当参数被更改后该回调会被调用
* @param type    参数存储类型
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern int app_conf_reg_int(char *name,int val,APP_CONF_HANDLE handle,APP_CONF_TYPE type);
/** 
* @brief 注册一个无符号整型的配置参数
* @param name    参数名
* @param val    配置参数默认值
* @param handle    参数回调，当参数被更改后该回调会被调用
* @param type    参数存储类型
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern int app_conf_reg_uint32(char *name,uint32_t val,APP_CONF_HANDLE handle,APP_CONF_TYPE type);
/** 
* @brief 注册一个配置参数的回调
* @param name    参数名
* @param handle    参数回调，当参数被更改后该回调会被调用
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 当一个进程已经注册了一个配置参数，另外一个进程想使用该参数时，可以调用该接口，然后通过回调函数获取参数值。
*/
extern int app_conf_reg_handle(char *name,APP_CONF_HANDLE handle);
/** 
* @brief 设置一个字符串类型的配置参数
* @param name    参数名
* @param val    配置参数值
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern int app_conf_set_string(char *name,char*val);
/** 
* @brief 设置一个整型的配置参数
* @param name    参数名
* @param val    配置参数值
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern int app_conf_set_int(char *name,int val);
/** 
* @brief 设置一个无符号整型的配置参数
* @param name    参数名
* @param val    配置参数值
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern int app_conf_set_uint32(char *name,uint32_t val);
/** 
* @brief 获取一个字符串类型的配置参数
* @param name    参数名
* @param val    配置参数值输出缓冲区
* @param val_size    配置参数值输出缓冲区大小
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern int app_conf_get_string(char *name,char *val,int val_size);
/** 
* @brief 设置一个整型的配置参数
* @param name    参数名
* @param out_val    配置参数值输出
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern int app_conf_get_int(char *name,int *out_val);
/** 
* @brief 设置一个无符号整型的配置参数
* @param name    参数名
* @param out_val    配置参数值输出
*
* @return 
*        -<em>0</em> 成功
*        -<em>!0</em> 失败
* @note 
*/
extern int app_conf_get_uint32(char *name,uint32_t *out_val);



extern int _has_uwb0;
extern int _has_uwb1;
extern int _has_uwb2;


int app_conf_reg_float(char *name,float val,APP_CONF_HANDLE handle,APP_CONF_TYPE type);
extern int app_conf_set_float(char *name,float val);
extern int app_conf_get_float(char *name,float *out_val);

#ifdef __cplusplus
}
#endif
#endif
