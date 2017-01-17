#ifndef USER_SESSION_H
#define USER_SESSION_H
#include "tuple5.h"
typedef struct _user_session
{
	void* self;   //挂载用户自己的定义的session
	tuple5 stream_flag;  //用来与捕获的数据包做比对，判断是C2S，还是S2C	
	struct _user_session* next;
}user_session_t;
typedef struct _user_session_pool
{
	user_session_t* free;
	user_session_t* used;
	int free_count;
	int used_count;
}user_session_pool;
int user_session_pool_init(user_session_t** head);

int user_session_pool_createlist(user_session_pool* pool ,int num);
user_session_t* user_session_pool_get(user_session_pool* pool);
int user_session_pool_return(user_session_pool* pool,user_session_t* session);
#endif
