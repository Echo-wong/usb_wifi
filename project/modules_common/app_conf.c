#include "app_conf.h"

#define APP_CONF_MAX_SIZE 128
static LIST * app_conf_list = NULL;
static pthread_mutex_t app_conf_lock = PTHREAD_MUTEX_INITIALIZER;
static uint32_t mod_id;

 int _has_uwb0=0;
 int _has_uwb1=0;
 int _has_uwb2=0;



typedef struct
{
    char name[APP_CONF_MAX_SIZE];
    char val[APP_CONF_MAX_SIZE];
    APP_CONF_HANDLE change_handle;
}APP_CONF;

static void app_conf_handle(MESSAGE *msg)
{
    if(msg->msg_id == MESSAGE_ID_CONF_PUSH)
    {
        char *prt = NULL;
        char *name,*val; 
        unsigned int i;
        char buf[APP_CONF_MAX_SIZE*2];
        if(strlen(msg->tag) < APP_CONF_MAX_SIZE*2)
        {
            strcpy(buf,msg->tag);
            name = strtok_r(buf,"=",&prt);
            val = strtok_r(NULL,"=",&prt);
            APP_CONF *conf;
            for(i = 0;i<app_conf_list->count;i++)
            {
                conf = ListGet(app_conf_list,i,APP_CONF);
                if(conf)
                {
                    if(strcmp(conf->name,name) == 0)
                    {
                        if(strcmp(conf->val,val) != 0)
                        {
                            pthread_mutex_lock(&app_conf_lock);
                            strcpy(conf->val,val);
                            pthread_mutex_unlock(&app_conf_lock);
                            if(conf->change_handle)
                            {
                                conf->change_handle(name,val);
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

void app_conf_init(uint32_t id)
{
    if(app_conf_list == NULL)
    {
        app_conf_list = NewListS();
        mod_id = id;
        modules_reg(id,app_conf_handle);
    }
}

int app_conf_reg_string(char *name,char*val,APP_CONF_HANDLE handle,APP_CONF_TYPE type)
{
    if(app_conf_list)
    {
        APP_CONF conf;
        char buf[APP_CONF_MAX_SIZE*2];
        if(strlen(name)+1 > APP_CONF_MAX_SIZE || strlen(val)+1 > APP_CONF_MAX_SIZE)
        {
            debug("para size error\n");
            return -1;
        }
       
        strcpy(conf.name,name);
        strcpy(conf.val,val);
        conf.change_handle = handle;
        ListAdd(app_conf_list,conf);
        snprintf(buf,sizeof(buf),"%s=%s",name,val);
        if(type == APP_CONF_TYPE_FILE)
        {
            msg_send(mod_id,ID_ENV_CONF,MESSAGE_ID_CONF_REG_FILE,buf,strlen(buf)+1);
        }
        else if(type == APP_CONF_TYPE_FLASH)
        {
            msg_send(mod_id,ID_ENV_CONF,MESSAGE_ID_CONF_REG_FLASH,buf,strlen(buf)+1);
        }
        else
        {
            msg_send(mod_id,ID_ENV_CONF,MESSAGE_ID_CONF_REG_RAM,buf,strlen(buf)+1);
        }
        return 0;
    }
    return -1;
}

int app_conf_reg_int(char *name,int val,APP_CONF_HANDLE handle,APP_CONF_TYPE type)
{
    char buf[APP_CONF_MAX_SIZE];
    snprintf(buf,sizeof(buf),"%d",val);
    return app_conf_reg_string(name,buf,handle,type);
}

int app_conf_reg_uint32(char *name,uint32_t val,APP_CONF_HANDLE handle,APP_CONF_TYPE type)
{
    char buf[APP_CONF_MAX_SIZE];
    snprintf(buf,sizeof(buf),"%u",val);
    return app_conf_reg_string(name,buf,handle,type);
}

int app_conf_reg_float(char *name,float val,APP_CONF_HANDLE handle,APP_CONF_TYPE type)
{
    char buf[APP_CONF_MAX_SIZE];
    snprintf(buf,sizeof(buf),"%f",val);
    return app_conf_reg_string(name,buf,handle,type);
}


int app_conf_reg_handle(char *name,APP_CONF_HANDLE handle)
{
    if(app_conf_list)
    {
        APP_CONF conf;
        if(strlen(name)+1 > APP_CONF_MAX_SIZE)
        {
            debug("para size error\n");
            return -1;
        }
        strcpy(conf.name,name);
        conf.val[0] = '\0';
        conf.change_handle = handle;
        ListAdd(app_conf_list,conf);
        msg_send(mod_id,ID_ENV_CONF,MESSAGE_ID_CONF_GET,name,strlen(name)+1);
        return 0;
    }
    return -1;
}

int app_conf_set_string(char *name,char*val)
{
    if(app_conf_list)
    {
        char buf[APP_CONF_MAX_SIZE*2];
        if(strlen(name)+1 > APP_CONF_MAX_SIZE || strlen(val)+1 > APP_CONF_MAX_SIZE)
        {
            debug("para size error\n");
            return -1;
        }
        snprintf(buf,sizeof(buf),"%s=%s",name,val);
        msg_send(mod_id,ID_ENV_CONF,MESSAGE_ID_CONF_SET,buf,strlen(buf)+1);
        return 0;
    }
    return -1;
}

int app_conf_set_int(char *name,int val)
{
    char buf[APP_CONF_MAX_SIZE];
    snprintf(buf,sizeof(buf),"%d",val);
    return app_conf_set_string(name,buf);
}

int app_conf_set_uint32(char *name,uint32_t val)
{
    char buf[APP_CONF_MAX_SIZE];
    snprintf(buf,sizeof(buf),"%u",val);
    return app_conf_set_string(name,buf);
}

int app_conf_set_float(char *name,float val)
{
    char buf[APP_CONF_MAX_SIZE];
    snprintf(buf,sizeof(buf),"%f",val);
    return app_conf_set_string(name,buf);
}


int app_conf_get_string(char *name,char *val,int val_size)
{
    if(app_conf_list)
    {
        unsigned int i;
        APP_CONF *conf;
        for(i = 0;i<app_conf_list->count;i++)
        {
            conf = ListGet(app_conf_list,i,APP_CONF);
            if(conf)
            {
                if(strcmp(conf->name,name) == 0)
                {
                    if((int)(strlen(conf->val)+1) > val_size)
                    {
                        return -1;
                    }
                    pthread_mutex_lock(&app_conf_lock);
                    strcpy(val,conf->val);
                    pthread_mutex_unlock(&app_conf_lock);
                    return 0;
                }
            }
            
        }
    }
    return -1;
}

int app_conf_get_int(char *name,int *out_val)
{
    char buf[APP_CONF_MAX_SIZE];
    if(app_conf_get_string(name,buf,APP_CONF_MAX_SIZE) == 0)
    {
        *out_val = atoi(buf);
        return 0;
    }
    return -1;
}

int app_conf_get_uint32(char *name,uint32_t *out_val)
{
    char buf[APP_CONF_MAX_SIZE];
    if(app_conf_get_string(name,buf,APP_CONF_MAX_SIZE) == 0)
    {
        *out_val = atoll(buf);
        return 0;
    }
    return -1;
}

int app_conf_get_float(char *name,float *out_val)
{
    char buf[APP_CONF_MAX_SIZE];
    if(app_conf_get_string(name,buf,APP_CONF_MAX_SIZE) == 0)
    {
        *out_val = atof(buf);
        return 0;
    }
    return -1;
}


int app_conf_printf(char *env_key)
{
    if(env_key)
    {
        char buf[APP_CONF_MAX_SIZE];
        printf("%s:",env_key);
        if(app_conf_get_string(env_key,buf,APP_CONF_MAX_SIZE) == 0)
        {
            printf("%s",buf);
        }
        printf("\n");
    }
    else
    {
        printf("para error\n");
    }
    return 1;
}

int app_conf_set(char *env)
{
    if(env)
    {
        char buf[APP_CONF_MAX_SIZE];
        char *p;
        char *key,*val;
        strcpy(buf,env);
        key = strtok_r(buf," ",&p);
        val = strtok_r(NULL," ",&p);
        if(key&&val)
        {
            if(app_conf_set_string(key,val) == 0)
            {
                printf("set %s=%s",key,val);
            }
            printf("\n");
            return 1;
        }
    }
    printf("para error\n");
    return 1;
}
