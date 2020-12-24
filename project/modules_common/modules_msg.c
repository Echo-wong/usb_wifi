#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <errno.h>
#include "modules_msg.h"

static int socket_list[256] = {0};
static int socket_client = -1;

static uint32_t mod_id;

const char *modules_name[] =
{
    "Environment",
    "Core",
    "Qt",
    "wifi",
    "ttl_lcd",
};

//#undef debug
//#define debug qDebug


static void socket_send_message(int fd,MESSAGE *msg)
{
    uint32_t flag = 0xDEADBEEF;
    send(fd, &flag, sizeof(uint32_t), 0);
    send(fd, msg, sizeof(MESSAGE), 0);
    if(msg->tag_size > 0)
    {
        flag = 0xDEADABBA;
        send(fd, &flag, sizeof(uint32_t), 0);
        send(fd, msg->tag, msg->tag_size, 0);
    }
    flag = 0xDEADDABB;
    send(fd, &flag, sizeof(uint32_t), 0);
}

static int socket_get_message(uint8_t *buffer,int buffer_len)
{
    int i, get_msg = 0;
    uint32_t flag;
    MESSAGE msg;
    for (i = 0; i < buffer_len;i++)
    {
        memcpy(&flag, buffer + i, sizeof(uint32_t));
        if(flag == 0xDEADBEEF)
        {
            memcpy(&msg, buffer + i + 4, sizeof(MESSAGE));
            i += 4 + sizeof(MESSAGE)-1;
            get_msg = 1;
        }
        else if(flag == 0xDEADABBA)
        {
            if(get_msg)
            {
                //printf("recv msg:%x,size:%d\n",msg.msg_id,msg.tag_size);
                if(mod_id == 0)
                {
                    msg_send(msg.sender_id, msg.receiver_id, msg.msg_id, buffer + i + 4, msg.tag_size);
                }
                else
                {
                    message_send(msg.sender_id, msg.receiver_id, msg.msg_id, buffer + i + 4, msg.tag_size);
                }
                return i  + 8 +  msg.tag_size;
            }
        }
        else if(flag == 0xDEADDABB)
        {
            if(get_msg)
            {
                //printf("recv msg:%x\n",msg.msg_id);
                if(mod_id == 0)
                {
                    msg_send(msg.sender_id, msg.receiver_id, msg.msg_id, NULL, 0);
                }
                else
                {
                    message_send(msg.sender_id, msg.receiver_id, msg.msg_id,NULL, 0);
                }
                return i +4;
            }
        }
    }
    return buffer_len;
}



static void message_tran_server_handle(MESSAGE *msg)
{
    if(msg->msg_id == MESSAGE_ID_TRAN)
    {
        MESSAGE *tmp_msg = ( MESSAGE *)msg->tag;
        if(tmp_msg->receiver_id == BROADCAST_MESSAGE)
        {
            unsigned int i;
            for(i = 0;i<255;i++)
            {
                if(socket_list[i] != -1 && i != (tmp_msg->sender_id >> 16))
                {
                    socket_send_message(socket_list[i],(MESSAGE*)msg->tag);
                }
            }
            message_free((MESSAGE*)msg->tag);
        }
        else if((tmp_msg->receiver_id >> 16) != mod_id && (tmp_msg->receiver_id >> 16) < 255)
        {
            int socket = socket_list[tmp_msg->receiver_id >> 16];
            if(socket >= 0)
            {
                socket_send_message(socket,(MESSAGE*)msg->tag);
                message_free((MESSAGE*)msg->tag);
            }
        }
    }
}

static void message_tran_clinet_handle(MESSAGE *msg)
{
    if(msg->msg_id == MESSAGE_ID_TRAN)
    {
        socket_send_message(socket_client,(MESSAGE*)msg->tag);
        message_free((MESSAGE*)msg->tag);
    }
}

static void* socket_message_recv(void* arg)
{
    int sock;
    int count,tmp_max_size = 512,tmp_size = 0,i,deal_count;
    uint8_t *tmp;
    if((int)arg < 0)
    {
        sock = socket_client;
    }
    else
    {
        sock = socket_list[(int)arg];
    }
    
    if(sock >= 0)
    {
        tmp = malloc(tmp_max_size);
        while(1)
        {
            count = read(sock, tmp + tmp_size, tmp_max_size - tmp_size);
            if(count > 0)
            {
                tmp_size += count;
                                
                #if 0
                {
                    int j;
                    printf("tmp:\n");
                    for (j = 0; j < tmp_size;j++)
                    {
                        printf("%x,",tmp[j]);
                    }
                    printf("\n");
                }
                #endif
                for (i = 0; i < tmp_size - 3;i++)
                {
                    if(tmp[i] == 0xBB && tmp[i+1] == 0xDA && tmp[i+2] == 0xAD && tmp[i+3] == 0xDE)
                    {
                        deal_count = socket_get_message(tmp,tmp_size);
                        
                        if(deal_count > 0 && tmp_size - deal_count > 0)
                        {
                            //printf("memmove\n");
                            memmove(tmp, tmp + deal_count, tmp_size - deal_count);
                        }
                        #if 0
                        {
                            int j;
                            printf("tmp2:\n");
                            for (j = 0; j < tmp_size;j++)
                            {
                                printf("%x,",tmp[j]);
                            }
                            printf("\n");
                        }
                        #endif
                        tmp_size -= deal_count;
                        //printf("tmp_size:%d\n",tmp_size);
                        if(tmp_size < 4)
                        {
                            break;
                        }
                        i = 0;
                    }
                }
            }
            else
            {
                close(sock);
                break;
            }
        }
        if((int)arg < 0)
        {
            socket_client = -1;
        }
        else
        {
            socket_list[(int)arg] = -1;
        }
        free(tmp);
    }
    
    return NULL;
}

static void* modules_server(void* arg)
{
    int sock = (int)arg;
    int client_sock;
    struct sockaddr_un  un;
    socklen_t client_addr_len;
    if(sock >= 0)
    {
        while(1)
        {
ACCEPT:
            client_addr_len = offsetof(struct sockaddr_un, sun_path) + 32;
            client_sock = accept(sock, (struct sockaddr *)&un, &client_addr_len);
            //printf("client_addr_len %d\n",client_addr_len);
            if (client_sock >= 0)
            {
                unsigned int i;
                for (i = 0; i < sizeof(modules_name) / sizeof(char *); i++)
                {
                    //printf("%s,%s\n", modules_name[i], (char *)un.sun_path + 6);
                    if (strcmp(modules_name[i], (char *)un.sun_path + 6) == 0)
                    {
                        pthread_t pid;
                        socket_list[i] = client_sock;
                        pthread_create(&pid, NULL, socket_message_recv, (void *)i);
                        debug("accept modules:%s\n", modules_name[i]);
                        goto ACCEPT;
                    }
                }
                close(client_sock);
            }
        }
    }
    return NULL;
}

int modules_msg_init_server(uint32_t id)
{
    int fd;
    pthread_t pid;
    struct sockaddr_un  un;
    unsigned int i;

    modules_reg((id<<16) + 1, message_tran_server_handle);
    mod_id = id;

    for (i = 0; i < sizeof(socket_list) / sizeof(int);i++)
    {
        socket_list[i] = -1;
    }
    un.sun_family = AF_UNIX;
    //strcpy((char*)un.sun_path + 1, modules_name[id]);
    un.sun_path[0] = '\0';
    snprintf(un.sun_path + 1, sizeof(un.sun_path) - 1, "/tmp/%s", modules_name[id]);

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		debug("socket failed\n");
        return -1;
	}

	if(bind(fd, (struct sockaddr *)&un, strlen(un.sun_path+1)  + offsetof(struct sockaddr_un, sun_path) + 2) < 0)
	{
		debug("bind failed :%d",errno);
        close(fd);
        return -1;
    }
	
    if (listen(fd, 10) < 0)
    {
        close(fd);
        return -1;
    }
    debug("server start\n");
    pthread_create(&pid, NULL, modules_server, (void*)fd);
    return 0;
}


int modules_msg_init_client(uint32_t id)
{
    pthread_t pid;
    int fd;
    struct sockaddr_un  un,server;


    modules_reg((id<<16) + 1, message_tran_clinet_handle);
    mod_id = id;

    un.sun_family = AF_UNIX;
    un.sun_path[0] = '\0';
    snprintf((char*)un.sun_path + 1, sizeof(un.sun_path) - 1, "/tmp/%s", modules_name[id]);

	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		debug("socket failed\n");
        return -1;
	}
    //printf("strlen(un.sun_path+1):%d\n", strlen(un.sun_path+1)  + offsetof(struct sockaddr_un, sun_path)+ 2);
    if(bind(fd, (struct sockaddr *)&un, strlen(un.sun_path+1)  + offsetof(struct sockaddr_un, sun_path)+ 2) < 0)
	{
		debug("bind failed");
        return -1;
    }
    server.sun_family = AF_UNIX;
    server.sun_path[0] = '\0';
    snprintf((char*)server.sun_path+1, sizeof(server.sun_path) - 1, "/tmp/%s", modules_name[0]);

    if(connect(fd, (struct sockaddr *)&server, strlen(server.sun_path+1)  + offsetof(struct sockaddr_un, sun_path)+ 2) != 0)
    {
        close(fd);
        printf("connect error:%d\n",errno);
        return -1;
    }
    socket_client = fd;
    pthread_create(&pid, NULL, socket_message_recv, (void*)-1);

    return 0;
}


void msg_send(uint32_t src_id, uint32_t dst_id, uint32_t msg_id, void *ex_data, int ex_data_len)
{
    if(dst_id != BROADCAST_MESSAGE)
    {
        if(mod_id == (dst_id>>16))
        {
            message_send(src_id,dst_id,msg_id,(uint8_t*)ex_data,ex_data_len);
        }
        else
        {
            MESSAGE msg;
            message_bulid(&msg,src_id,dst_id,msg_id,(uint8_t*)ex_data,ex_data_len);
            message_send(src_id,BROADCAST_MESSAGE,MESSAGE_ID_TRAN,(uint8_t*)&msg,sizeof(MESSAGE));
        }
    }
    else
    {
        MESSAGE msg;
        message_bulid(&msg,src_id,dst_id,msg_id,(uint8_t*)ex_data,ex_data_len);
        message_send(src_id,BROADCAST_MESSAGE,msg_id,(uint8_t*)ex_data,ex_data_len);
        message_send(src_id,BROADCAST_MESSAGE,MESSAGE_ID_TRAN,(uint8_t*)&msg,sizeof(MESSAGE));
    }
}
