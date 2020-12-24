#ifndef _MODULES_ID_H
#define _MODULES_ID_H

//添加新进程应用除了需要在下面的枚举量中添加进程ID外，还需要在modules_name中添加进程名字。
enum
{
    ID_ENV_APP,
    ID_CORE_APP,
    ID_QT_APP,
    ID_WIFI_APP,
    ID_TTL_LCD_APP,
};

extern const char *modules_name[];

enum
{
    ID_ENV_MODULE = (ID_ENV_APP<<16),
    ID_ENV_TRANSMIT,
    ID_ENV_CONF,
};

enum
{
    ID_CORE_MODULE = (ID_CORE_APP<<16) ,
    ID_CORE_TRANSMIT,
    ID_CORE_TEST,
    ID_CORE_CONF,
    ID_CORE_CONSOLE,
    ID_CORE_BACKUP,
    ID_CORE_ALARM
};


enum
{
    ID_QT_MODULE = (ID_QT_APP<<16) ,
    ID_QT_TRANSMIT,
    ID_QT_CONF,
    ID_QT_CONSOLE,
    ID_QT_UWBINFO,
};

enum
{
    ID_WIFI_MODULE = (ID_WIFI_APP<<16) ,
    ID_WIFI_TRANSMIT,
    ID_WIFI_CONF,
};

enum
{
    ID_TTL_LCD_MODULE = (ID_TTL_LCD_APP<<16) ,
	ID_TTL_LCD_CONF,
    ID_TTL_LCD_SYSINFO,
};


#endif
