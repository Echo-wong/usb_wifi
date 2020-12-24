#ifndef _LIB_M_CTRL_H
#define _LIB_M_CTRL_H


typedef void (*exit_callback)(char * reason);

typedef int (*lpc_cmd_handler)(char *);
typedef struct {
	char *name;
	lpc_cmd_handler func;
	char *help;
	char *doc;
}LPC_COMMAND,*LPC_COMMAND_P;



typedef struct mission_ctrl_t
{
	char name[32];
	char prompt[64];
	char his_name[64];		//history file name
	char last_in_his[256];

	char unix_socket;			//is using unix socket

	exit_callback exit_cb;
	
	LPC_COMMAND *commands;
	void *priv;		//private data -> MCTRL_PRIVATE_T
}MCTRL_T,*MCTRL_P;




extern MCTRL_P mc_new(char *mc_name,char *prompt,LPC_COMMAND commands[],char unix_socket);
extern int mc_start(MCTRL_P me);
extern int mc_shutdown(MCTRL_P me);
extern void mc_delete(MCTRL_P me);

extern void mc_register_exit_callback(MCTRL_P me,exit_callback cb);

//MAKE SURE you have called mc_new *first* <!-before-!> you can call mc_out or MC_OUT!!!!
extern void mc_out(const char *fmt,...);

#define MC_DEBUG(argc,argv...) ({mc_out("\033[33m%10.10s %10.10s %04d\033[0m => ",__FILE__,__func__,__LINE__);mc_out(argc,##argv);mc_out("\n"); }) 



#endif

