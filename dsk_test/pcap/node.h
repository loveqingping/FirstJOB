#ifndef NODE_H
#define NODE_H
#include "user_session.h"
#include <stdint.h>
typedef struct node    //五元组
{
	tuple5 key;
	user_session_t* user_session;
	struct node* next;
}node;
typedef struct node_pool
{
	node* free;
	node* used;
	uint32_t free_count;
	uint32_t used_count;
}node_pool;
int node_pool_init(node** head);
int node_pool_create_list(node_pool* pool,int num);
node*  node_pool_get(node_pool* pool);
int node_pool_return(node_pool* pool,node* p);
node* node_pool_find(node_pool* pool,tuple5* p);
#endif
