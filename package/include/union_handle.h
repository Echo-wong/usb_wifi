#ifndef _UNION_HANDLE_H_
#define _UNION_HANDLE_H_

typedef void * UNION_HANDLE;
extern void *union_handle_new(void);
extern void union_handle_free(void *handle);
extern int union_handle_add_key(void *handle, const char *key_name, void *key);
extern void *union_handle_get_key(void *handle, const char *key_name);
#endif