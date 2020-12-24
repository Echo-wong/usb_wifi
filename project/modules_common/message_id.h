#ifndef _MESSAGE_ID_H
#define _MESSAGE_ID_H
enum
{
    MESSAGE_ID_TRAN,
    
    //配置变量相关
    MESSAGE_ID_CONF_REG_FILE,  //注册变量，储存于文件中
    MESSAGE_ID_CONF_REG_RAM,   //注册变量，只缓存于内存
    MESSAGE_ID_CONF_REG_FLASH, //注册变量，储存于FLASH中
    MESSAGE_ID_CONF_GET,    //获取变量
    MESSAGE_ID_CONF_SET,    //设置变量
    MESSAGE_ID_CONF_PUSH,   //推送变量

    MESSAGE_ID_CONSOLE_MSG,   //终端消息
    MESSAGE_ID_CONSOLE_OPEN,   //打开QT终端
    MESSAGE_ID_CONSOLE_CLOSE,   //关闭QT终端
    MESSAGE_ID_TCP_CONSOLE_OPEN,   //打开TCP终端
    MESSAGE_ID_TCP_CONSOLE_CLOSE,   //关闭TCP终端

    MESSAGE_ID_BACKUP_MSG,
    MESSAGE_ID_ALARM_MSG,
    MESSAGE_ID_CTWAVE_MSG,
    MESSAGE_ID_UWBINFO_MSG,
    MESSAGE_ID_BACKIMG_MSG,
    MESSAGE_ID_UWBINFO_SERVER_MSG,

	MESSAGE_ID_UWBCHANNEL_MSG,

	MESSAGE_ID_UWB_TAG_AGING_TIME,

	MESSAGE_ID_TTL_LCD_NETWORK_STATUS,
	MESSAGE_ID_TTL_LCD_TOTAL_TAGS,
	MESSAGE_ID_TTL_LCD_TAG_INFO,

	MESSAGE_ID_QT_CMD_MCU_OTA,
	MESSAGE_ID_QT_MSGBOX,
	
	MESSAGE_ID_QT_TAG_INFO_MSG_V2,
    
};

#endif
