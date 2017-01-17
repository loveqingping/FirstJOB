#include "user_session.h"
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
int user_session_pool_init(user_session_t** head)
{
	user_session_t* p = NULL;
	p = (user_session_t* )calloc(1,sizeof(user_session_t) );
	if(p == NULL)
	{
		fprintf(stderr,"error in %s:%d\n",__func__,__LINE__);
		exit(-1);
	}
	else
	{
		p->self = NULL;
		p->next = NULL;
		*head = p;
		return 0;
	}
} 
int user_session_pool_createlist(user_session_pool* pool ,int num)
{

	user_session_pool_init(&(pool->free));
	user_session_pool_init(&(pool->used));
	user_session_t* pfree = pool->free;
	user_session_t* pused = pool->used;
	int i = 0;
	user_session_t* p = NULL;
	for(i = 0; i < num; ++i)
	{
		p = calloc(1,sizeof(user_session_t));
		bzero(p,sizeof(user_session_t) );
		p->next = pfree->next;
		pfree->next = p;
	}
	pool->free_count = num;
	pool->used_count = 0;
	return 0;
}
user_session_t* user_session_pool_get(user_session_pool* pool)
{
	user_session_t* pfree = pool->free;
	user_session_t* pused = pool->used;
	user_session_t* p1 = pfree->next;
	user_session_t* p2 = pfree->next->next;
	
	p1->next = pused->next;
	pused->next = p1;
	
	pfree->next = p2;
	
	return p1;
}
int user_session_pool_return(user_session_pool* pool,user_session_t* session)
{
	user_session_t* pfree = pool->free;
	user_session_t* pused = pool->used;
	user_session_t* ptemp = pool->used;
	while(ptemp->next != NULL)
	{
		if(ptemp->next = session)
		{
			break;
		}
		ptemp = ptemp->next;
	}
	if(ptemp->next == NULL)
	{
		fprintf(stderr,"error in %s:%d\n",__func__,__LINE__);
		exit(-1);
	}
	ptemp->next = session->next;
	session->next = pfree->next;
	pfree->next = session;
	if(session->self != NULL)
	{
		free(session->self);
		session->self = NULL;
	}
	return 0;
}

