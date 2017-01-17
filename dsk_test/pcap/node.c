#include "node.h"
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
int node_pool_init(node** head)
{
	node* p = NULL;
	p = calloc(1,sizeof(node));
	if( p == NULL)
	{
		fprintf(stderr,"error in %s:%d\n",__func__,__LINE__);
		return -1;
	}
	else
	{
		p->next = NULL;
		p->user_session = NULL;
		*head = p;
		return 0;
	}
}
int node_pool_create_list(node_pool* pool, int num)
{
	int i = 0;
	node_pool_init(&(pool->free));
	node_pool_init(&(pool->used));
	node* pfree = pool->free;
	node* pused = pool->used;
	node* p = NULL;
	for(i = 0; i < num; ++i)
	{
		p = calloc(1,sizeof(node) );
		bzero(p,sizeof(node));
		p->next = pfree->next;
		pfree->next = p;
	}
	pool->free_count = num;
	pool->used_count = 0;
	return 0;
}
node* node_pool_get(node_pool* pool)
{
	node* pfree = pool->free;
	node* pused = pool->used;
	node* p1 = pfree->next;
	node* p2 = pfree->next->next;
	
	p1->next = pused->next;
	pused->next = p1;
	
	pfree->next = p2;
	pool->free_count--;
	pool->used_count++;
	return pused->next;
}
int node_pool_return(node_pool* pool, node* p)
{
	node* pfree = pool->free;
	node* pused = pool->used;
	node* ptemp = pool->used;
	while(ptemp->next != NULL)
	{
		if(ptemp->next == p)
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
	ptemp->next = p->next;
	p->next = pfree->next;
	pfree->next = p;
	pool->free_count++;
	pool->used_count--;
	return 0;
	
}
static int tuple5_if_eq(tuple5* p1,tuple5* p2)
{
	if( 0 == memcmp(p1,p2,sizeof(tuple5)) )
	{
		return 0;
	}
	else
	{
		if( (p1->source == p2->dest) && (p1->dest == p2->source) &&
				(p1->saddr == p2->daddr) && (p1->daddr == p2->saddr))
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
}
node* node_pool_find(node_pool* pool, tuple5* p)
{
	node* pfree = pool->free;
	node* pused = pool->used;
	node* ptemp = pool->used->next;    //指向第一个节点
	while(ptemp != NULL)
	{
		if(0 == tuple5_if_eq(&(ptemp->key),p)  )
		{
			return ptemp;
		}
		ptemp = ptemp->next;
	}
	if(ptemp == NULL)
	{
		return NULL;
	}
}
