#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules_msg.h"
#include "app_conf.h"

#define STARTUP_STA_MODE	"/home/root/app/sta_open.sh"
#define CANNEL_STA_MODE		"/home/root/app/sta_close.sh"

#define STARTUP_AP_MODE		"/home/root/app/hostap/ap_open1.sh"
#define CANNEL_AP_MODE		"/home/root/app/hostap/ap_close1.sh"

#define WIFI_DRIVER			"/home/root/app/rtl8192_boot.sh"
#define REMOVE_WIFI_DRIVER	"rmmod 8192eu"

#define HOSTAPD_CONFIG		"/home/root/app/hostap/hostapd.conf"
#define WPA_SUPPLICANT_CONFIG	"/etc/wpa_supplicant.conf"

#define EXIT				"q"

#define AP_MODE				1
#define STA_MODE			2	

/******************************************************/

#define AP_MAX_CMD				255
#define MAX_LENTH			128

#define	AP_CMD_SSID_PARAM				"sed -i 's/^ssid=.*/ssid=%s/' /home/root/app/hostap/hostapd.conf"						// SSID对应的CMD
#define	AP_CMD_WPA_PASSPHRASE_PARAM		"sed -i 's/^wpa_passphrase=.*/wpa_passphrase=%s/' /home/root/app/hostap/hostapd.conf"

// AP模式对应的参数和命令
// 与参数数组相对应，第三个为"ssid",则对应的处理命令也是为第三个
char ap_cmd_array[AP_MAX_CMD][MAX_LENTH] = {
	AP_CMD_WPA_PASSPHRASE_PARAM,
	" ",								// 留空测试遍历效果
	AP_CMD_SSID_PARAM
};

/******************************************************/
// 参数数组，存放hostapd.config的参数
#define AP_MAX_PARAM			255

char ap_param_array[AP_MAX_PARAM][MAX_LENTH] = {
	"wpa_passphrase",
	"wpa_key_mgmt",
	"ssid"
};

/******************************************************/

// STA模式对应的参数和命令

#define	STA_CMD_SSID_PARAM				"sed -i 's/^ssid=.*/ssid=\"TGY-WIFI-CP\"/' /etc/wpa_supplicant.conf"
#define	STA_CMD_PSK_PARAM				"sed -i 's/^psk=.*/psk=\"tgyxxkj888\"/' /etc/wpa_supplicant.conf"
#define	STA_CMD_KEY_MGMT_PARAM			"sed -i 's/^key_mgmt=.*/key_mgmt=WPA-PSK/' /etc/wpa_supplicant.conf"

#define STA_MAX_CMD			32

char sta_cmd_array[STA_MAX_CMD][MAX_LENTH] = {
	STA_CMD_SSID_PARAM,
	STA_CMD_PSK_PARAM,
	STA_CMD_KEY_MGMT_PARAM
};

#define STA_MAX_PARAM		32

// 参数数组，存放wpa_supplicant的参数
char sta_param_array[STA_MAX_PARAM][MAX_LENTH] = {
	"ssid",
	"psk",
	"key_mgmt"
};



/****************sta***************/
static inline void sta_open(void)
{
	system(STARTUP_STA_MODE);
}

static inline void sta_close(void)
{
	system(CANNEL_STA_MODE);
}
/**********************************/
/****************ap****************/
static inline void ap_open(void)
{
	system(STARTUP_AP_MODE);
}

static inline void ap_close(void)
{
	system(CANNEL_AP_MODE);
}
/****************ap****************/




static char *get_param(char *path, char *param)
{
	static char param_buff[256];
	char buff[512];
	
	FILE *f = fopen(path, "r");
	if(f != NULL)
	{
		char *tok,*p;
		while(fgets(buff,512,f))
		{
			tok = strtok_r(buff, "= \n", &p);
			if(strcmp(tok,param) == 0)
			{
				tok = strtok_r(NULL, "= \n", &p);
				if(tok)
				{
					strcpy(param_buff,tok);
					fclose(f);
					return param_buff;
				}
			}
		}
		fclose(f);
	}
	
	return NULL;
}



static void set_param(char *param, char *cmd_name, int mode)
{
	int i;
	
	if(mode == AP_MODE)
	{
		for(i=0; i<AP_MAX_PARAM; i++)
		{
			if(0 == strcmp(ap_param_array[i], cmd_name))
				break;
		}
		
		char *old_param = get_param(HOSTAPD_CONFIG, ap_param_array[i]);
		
		if(old_param)
		{
			printf("------------------------------------\n");
			printf("old_param: %s, new_param: %s\n",old_param, param);
			if(strcmp(param, old_param) != 0)
			{
				char buff[512] = {0};
				printf("set param: %s\n",param);
				
				// 对应参数数组，第三个就对应第三条命令
				snprintf(buff, sizeof(buff), ap_cmd_array[i], param);
				printf("cmd: %s\n",buff);
				system(buff);
			}
			printf("------------------------------------\n");
		} 
	}
	
	if(mode == STA_MODE)
	{
		for(i=0; i<STA_MAX_PARAM; i++)
		{
			if(0 == strcmp(sta_param_array[i], cmd_name))
				break;
		}
		
		char *old_param = get_param(WPA_SUPPLICANT_CONFIG, sta_param_array[i]);
		
		if(old_param)
		{
			printf("------------------------------------\n");
			printf("old_param: %s, new_param: %s\n",old_param, param);
			if(strcmp(param, old_param) != 0)
			{
				char buff[512] = {0};
				printf("set param: %s\n",param);
				
				// 对应参数数组，第三个就对应第三条命令
				snprintf(buff, sizeof(buff), sta_cmd_array[i], param);
				printf("cmd: %s\n",buff);
				system(buff);
			}
			printf("------------------------------------\n");
		} 
		
	}
	
}

// 参数回调，当参数被更改后该回调会被调用
static void set_param_handle(char *name, char *val)
{
	char param[256];
	
	// 1.设置新的值
	// 2.读取配置值
	// 3.写入配置值
	app_conf_reg_string(name, val, set_param_handle, APP_CONF_TYPE_FILE);
	app_conf_get_string(name, param, sizeof(param));
	set_param(param, name, 0);	
}


// 检查无线wifi开启情况
int check_wifi_enable(void)
{
	int ret = -1;
	char buf[512];
	FILE *fb = popen("iwconfig wlan0","r");
	if(fb)
	{
		//sleep(3);
		while(fgets(buf, sizeof(buf), fb))
		{
			//printf("%s\n",buf);				
			// 如果是AP或者STA模式			
			if(strstr(buf,"Mode:Master") != NULL)			
			{
				ret = AP_MODE;
			}
			if(strstr(buf,"Mode:Managed") != NULL)			
			{
				ret = STA_MODE;
			}
		}
		pclose(fb);
	}
	// 其他模式或者没有打开就返回负值
	return ret;
}




int main(int argc,char *argv[])
{
	int ret = -1;
	char param[256];
	
	
	printf("---usb wifi test---.\n");
	
	
	if(NULL == argv[1])
	{
		// 检测wifi是否已经打开AP或者STA模式，打开则不必重复
		ret = check_wifi_enable();
		if(ret == AP_MODE || ret == STA_MODE)
		{
			printf("wifi is already set.\n");
			return 0;
		}

		printf("-----------\n");
		printf("-----------\n");
		printf("-----------\n");
		printf("------INIT PROCESS-----\n");	
		message_sys_init();
		
		ret = modules_msg_init_client(ID_WIFI_APP);
		printf("ret = %d.\n", ret);
		
		app_conf_init(ID_WIFI_CONF);
		printf("-----------\n");

		app_conf_reg_string("ssid", "chihwa test", set_param_handle, APP_CONF_TYPE_FILE);
		
		printf("-----------\n");
		printf("----- test------\n");
		
		app_conf_get_string("ssid", param, sizeof(param)); 	// 从配置参数中获取wifi的ssid
		
		msg_send(ID_WIFI_CONF, ID_WIFI_APP, MESSAGE_ID_CONF_SET, param, sizeof(param));
		printf("*******SUCCESS**********\n");
		
		app_conf_reg_string("wpa_passphrase", "1234567890", set_param_handle, APP_CONF_TYPE_FILE);
		
		app_conf_get_string("ssid", param, sizeof(param)); 	// 从配置参数中获取wifi的ssid
		set_param(param, "ssid", AP_MODE);
		
		
		printf("-----------\n");
		
		memset(param, 0, sizeof(param));
		
		app_conf_get_string("wpa_passphrase", param, sizeof(param));	// 从配置参数中获取wifi的wpa_passphrase
		set_param(param, "wpa_passphrase", AP_MODE);
		
		// 默认开启AP模式
		system(WIFI_DRIVER);	
		
		ap_open();
	
		printf("AP OK\n");	
		printf("-----------\n");
		
		return 0;
	}
	
	
	// 退出的时候关闭进程，卸载wifi驱动
	if(0 == strcmp("q", argv[1]))
	{	
		system(CANNEL_AP_MODE);
		system(CANNEL_STA_MODE);
		system(REMOVE_WIFI_DRIVER);	
		
		return 0;
	};

	
	// 检测wifi打开的是什么模式，与设置相同就直接退出即可
	ret = check_wifi_enable();
		
	// 得到设置值是AP还是STA模式与当前开启模式相比，相同则可以退出
	if(ret == AP_MODE && (0 == strcmp("AP", argv[1]) || 0 == strcmp("ap", argv[1])))
	{
		printf("It is AP mode now.\n");
		return 0;
	}
	
	if(ret == STA_MODE && (0 == strcmp("STA", argv[1]) || 0 == strcmp("sta", argv[1])))
	{
		printf("It is STA mode now.\n");
		return 0;
	}
		
	
	// 需要进行AP或STA模式的转换
	// 若当前是STA模式，转换成AP模式不需要卸载驱动，直接杀进程即可
	if(ret == STA_MODE && (0 == strcmp("AP", argv[1]) || 0 == strcmp("ap", argv[1])))
	{
		sta_close();
		
		ap_open();
	
		printf("STA to AP OK\n");	
		printf("-----------\n");
		
		return 0;
	}
	
	// 若当前是AP模式，转换STA模式需要卸载驱动，再转换
	if(ret == AP_MODE && (0 == strcmp("STA", argv[1]) || 0 == strcmp("sta", argv[1])))
	{
		ap_close();
		
		system(REMOVE_WIFI_DRIVER);
		
	
		// 默认配置是TGY-WIFI-CP
		app_conf_reg_string("ssid", "TGY-WIFI-CP", set_param_handle, APP_CONF_TYPE_FILE);
		app_conf_reg_string("psk", "tgyxxkj888", set_param_handle, APP_CONF_TYPE_FILE);
		app_conf_reg_string("key_mgmt", "WPA-PSK", set_param_handle, APP_CONF_TYPE_FILE);
	
		memset(param, 0, sizeof(param));
		
		app_conf_get_string("ssid", param, sizeof(param)); 	// 从配置参数中获取wifi的ssid
		set_param(param, "ssid", STA_MODE);
		
		memset(param, 0, sizeof(param));
		
		app_conf_get_string("psk", param, sizeof(param)); 	// 从配置参数中获取wifi的psk
		set_param(param, "psk", STA_MODE);
		
		memset(param, 0, sizeof(param));
		
		app_conf_get_string("key_mgmt", param, sizeof(param)); 	// 从配置参数中获取wifi的key_mgmt
		set_param(param, "key_mgmt", STA_MODE);
		
		system(WIFI_DRIVER);
		
		sta_open();
	
		printf("AP to STA OK\n");	
		printf("-----------\n");
		
		return 0;
	}
	
	
	printf("please enter the right mode.\n");
	return 0;
}








