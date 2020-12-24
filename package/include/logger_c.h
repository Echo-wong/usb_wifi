#ifndef _LOGGER_C_H
#define _LOGGER_C_H


#include <stdint.h>



typedef enum logger_prio_t
{
	LOG_DISABLED=0,
	LOG_PRI_FATAL,
	LOG_PRI_ERROR,
	LOG_PRI_WARN,
	LOG_PRI_NOTICE,
	LOG_PRI_DEBUG,
	LOG_PRI_TRACE,
}LOG_PRIO_T;


typedef struct logger_client_tag
{	
	//public
	int enable_stdout;		//ʹ�ܱ�׼���
	int enable_timestamp;	//ʹ��ʱ�����ʾ
	int enable_socket;		//ʹ��unix socket����
	int level;					//��־����
		
	void (*fatal)(struct logger_client_tag* me,const char *fmt, ...);
	void (*error)(struct logger_client_tag* me,const char *fmt, ...);
	void (*warn)(struct logger_client_tag* me,const char *fmt, ...);
	void (*notice)(struct logger_client_tag* me,const char *fmt, ...);
	void (*debug)(struct logger_client_tag* me,const char *fmt, ...);
	void (*trace)(struct logger_client_tag* me,const char *fmt, ...);


	//private	-- ��Ҫ��
	char name[32];			//ģ������
	char tname[36];
	char so_path[64];
	char *buffer;	
	uint32_t magic;
	int fd;
	void *host_addr;
	uint32_t log_size;	
}LOGGER_T,*LOGGER_P;



extern void		logger_delete(LOGGER_P me);
extern LOGGER_P	logger_new(const char *name, LOG_PRIO_T level);
extern char* 		logger_version(void);







#endif
