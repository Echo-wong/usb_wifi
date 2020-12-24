#ifndef	 _DEBUG_H
#define	 _DEBUG_H
#include <stdint.h>
#include <stdio.h>

#ifndef __cplusplus
#define TERM_NONE       "\033[0m"
#define TERM_RED        "\033[31m"
#define TERM_GREEN      "\033[32m"
#define TERM_YELLOW     "\033[33m"
#define TERM_BLUE       "\033[34m"


//#define debug(argc,...) {printf(TERM_YELLOW "%10.10s %10.10s %04d " TERM_NONE "=> ",__FILE__,__func__,__LINE__);printf(argc,##__VA_ARGS__); }

#define Exception(argc,...) {printf(TERM_RED "%10.10s %10.10s %04d " TERM_NONE "=> ",__FILE__,__func__,__LINE__);printf(argc,##__VA_ARGS__);}
#define exception(argc,...) {printf(TERM_RED "%10.10s %10.10s %04d " TERM_NONE "=> ",__FILE__,__func__,__LINE__);printf(argc,##__VA_ARGS__);}

extern void debug(char *fmt, ...);
extern void print(char *fmt, ...);
extern void printb(char *s, uint8_t *array, int len);
extern void print_progress(char *s, double progress);
#endif
#endif
