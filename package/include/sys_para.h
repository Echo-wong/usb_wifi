#ifndef _SYS_PARA_H_
#define _SYS_PARA_H_

#ifdef __cplusplus
extern "C"
{
#endif
///配置参数更新回调函数 key：键值 value：配置参数值
typedef void (*SYS_PARA_CALLBACK)(const char *key,const char *value);

/** 
* @brief 打开参数配置服务端
* @param conf_a_path    配置文件A存储路径，为NULL时使用默认路径：CONF_FILE_A_PATH
* @param conf_b_path    配置文件B存储路径，为NULL时使用默认路径：CONF_FILE_B_PATH
* @param conf_default_path    初始化值配置文件存储路径，为NULL时使用默认路径：CONF_FILE_DEFAULT_PATH
* 
* @return 返回服务端句柄
*        -<em>NULL</em> fail
*        -<em>!NULL</em> succeed
*/
extern void *sys_para_server_open(char *conf_a_path,char *conf_b_path,char *conf_default_path);
/** 
* @brief 关闭参数配置服务端
* @param handle   服务端句柄
*/
extern void sys_para_server_close(void *handle);
/** 
* @brief 打开参数配置客户端
* 
* @return 返回客户端句柄
*        -<em>NULL</em> fail
*        -<em>!NULL</em> succeed
*/
extern void *sys_para_client_open(void);
/** 
* @brief 关闭参数配置客户端
* @param handle   客户端句柄
*/
extern void sys_para_client_close(void *handle);
/** 
* @brief 注册配置参数
* @param handle    客户端句柄
* @param key    配置参数键值
* @param default_val    配置参数默认值
* 
* @return 返回服务句柄
*        -<em>!0</em> fail
*        -<em>0</em> succeed
*/
extern int sys_para_reg(void *handle,char *key,char *default_val);
/** 
* @brief 获取配置参数，值拷贝输出到out_str中
* @param handle    客户端句柄
* @param key    配置参数键值
* @param out_str    配置参数值输出
* @param out_str_len    out_str最大长度
* 
* @return 返回服务句柄
*        -<em>!0</em> fail
*        -<em>0</em> succeed
*/
extern int sys_para_get_string(void *handle,char *key,char *out_str,int out_str_len);
/** 
* @brief 设置配置参数
* @param handle    客户端句柄
* @param key    配置参数键值
* @param val    配置参数值
* 
* @return 返回服务句柄
*        -<em>!0</em> fail
*        -<em>0</em> succeed
*/
extern int sys_para_set_string(void *handle,char *key,char *val);
/** 
* @brief 设置配置参数更新回调函数
* @param callback    回调函数
*/
extern void sys_para_set_callback(void *handle,SYS_PARA_CALLBACK callback);

/** 
* @brief 获取库版本信息
*/
#define sys_para_get_version() "0.1.0"
#ifdef __cplusplus
}
#endif
#endif