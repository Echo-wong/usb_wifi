#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STARTUP_STA_MODE	"/home/root/app/sta_open.sh"
#define CANNEL_STA_MODE		"/home/root/app/sta_close.sh"

#define STARTUP_AP_MODE		"/home/root/app/hostap/ap_open1.sh"
#define CANNEL_AP_MODE		"/home/root/app/hostap/ap_close1.sh"

#define REMOVE_WIFI_DRIVER	"rmmod 8192eu"

#define EXIT				"q"

static void rtl8192eu_init(void)
{
	system("/home/root/app/rtl8192_boot.sh");
}


/****************sta***************/
static void sta_open(void)
{
	system(STARTUP_STA_MODE);
}

static void sta_close(void)
{
	system(CANNEL_STA_MODE);
}
/**********************************/


/****************ap****************/
static void ap_open(void)
{
	system(STARTUP_AP_MODE);
}

static void ap_close(void)
{
	system(STARTUP_AP_MODE);
}
/****************ap****************/


int check_wifi_enable(void)
{
	int ret = -1;
	char buf[512];
	FILE *fb = popen("iwconfig wlan0","r");
	if(fb)
	{
		sleep(3);
		while(fgets(buf, sizeof(buf), fb))
		{
			printf("%s\n",buf);
			if(strstr(buf,"Mode:Master") != NULL)
			{
				ret = 0;
			}
		}
		pclose(fb);
	}
	return ret;
}

int main(int argc,char *argv[])
{
	int ret = -1;
	
	printf("---hello world---.\n");
	if(NULL == argv[1])
	{
		printf("please input WIFI MODE.\n");
		return -1;
	}
	
	
	// 退出的时候关闭进程，卸载wifi驱动
	if(0 == strcmp("q", argv[1]))
	{	
		system(CANNEL_AP_MODE);
		system(CANNEL_STA_MODE);
		system(REMOVE_WIFI_DRIVER);	
		
		return 0;
	};
	
	// 检查网卡开启模式，没有则返回-1
	ret = check_wifi_enable();
	
	printf("\n");
	printf("ret=%d\n", ret);
		
	
	// 默认开启AP模式
	if(0 == strcmp("AP", argv[1]))
	{
		rtl8192eu_init();
		ap_open();
	
		printf("AP OK\n");	
		printf("-----------\n");	
	}
	
	printf("argv[1]=%s \n", argv[1]);
	
	if(0 == strcmp("STA", argv[1]))
	{
		rtl8192eu_init();
		sta_open();

		printf("STA OK\n");
		printf("+++++++++++\n");
	}
	
	return 0;
}









