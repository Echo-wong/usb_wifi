#ifndef _KEY_FILE_H_
#define _KEY_FILE_H_
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "cctypes.h"
#include "queue.h"

typedef struct _KEY_FILE KEY_FILE;
struct _KEY_FILE
{
    char *file_path[2];
    LIST *para_list;
    int (*get_key_val_index)(KEY_FILE *key_file,int index,char *key_out,char *val_out);
    int (*get_val)(KEY_FILE *key_file,char *key,char *val_out);
    int (*set_val)(KEY_FILE *key_file,char *key,char *val);
};
extern KEY_FILE *c_key_file_new(char *file_a, char *file_b);
#endif 