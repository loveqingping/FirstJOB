#include "mystack.h"
#include "http_session.h"
int tcp_read(tcp_stream_t* ts,void**pme)
{
	http_session_t* session = NULL;
	if(*pme == NULL)
	{
		session = http_session_malloc();
	}
	else
	{
		session = *pme;
	}
	if(ts->flag == S2C_DATA)
	{
		printf("S2C_DATA:%s\n",ts->toclient);
	}
	else
	{
		printf("C2S_DATA:%s\n",ts->toserver);
	}
	return 0;
}
int main(int argc,char* argv[])
{
	node_pool np;
	user_session_pool sp;
	node_pool_create_list(&np,4096);
	user_session_pool_createlist(&sp,4096);	
	stack_run(argv[1],&np,&sp, tcp_read);
	return 0;
}
