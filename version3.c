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

#define EXIT				"q"

#define AP_MODE				1
#define STA_MODE			2	


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
	return ret;
}


int main(int argc,char *argv[])
{
	int ret = -1;
	
	printf("---usb wifi test---.\n");
	
	//message_sys_init();
	modules_msg_init_client(ID_WIFI_APP);
	app_conf_init(ID_WIFI_CONF);
	
	
	if(NULL == argv[1])
	{
		// 检测wifi是否已经打开AP或者STA模式，打开则不必重复
		ret = check_wifi_enable();
		if(ret == AP_MODE || ret == STA_MODE)
		{
			printf("wifi is already set.\n");
			return 0;
		}	
		
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
	if(ret == AP_MODE && 0 == strcmp("AP", argv[1]))
	{
		printf("It is AP mode now.\n");
		return 0;
	}
		
	
	if(ret == STA_MODE && 0 == strcmp("STA", argv[1]))
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
		system(WIFI_DRIVER);
	
		sta_open();
	
		printf("AP to STA OK\n");	
		printf("-----------\n");
		
		return 0;
	}
	
	
	printf("please enter the right mode.\n");
	return 0;
}









