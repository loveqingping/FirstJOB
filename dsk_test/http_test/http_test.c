#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <malloc.h>
void* http_send(void* arg)
{
	int st = *((int*)arg) ;  //取得socket
	char* request = "GET / HTTP/1.0\r\nHost: www.kun.com\r\nUser-Agent: ApacheBench/2.3\r\nAccept: */*\r\n\r\n";
	char req[2048];
	bzero(req, 2048);
	strncpy(req, request, strlen(request));
	send(st, req, strlen(req), 0);
	return NULL;
}
void* http_recv(void* arg)
{
	int n = 0;
	int st = *((int*)arg);  //取得socket
	char res[2048];
	while(1)
	{
		bzero(res, 2048);
		n = recv(st, res, 2048,0);	
		if(n == 0 || n == -1)
		{
			break;
		}
		fprintf(stderr,"%s", res);
	}
	return NULL;

}
int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		fprintf(stderr,"Usage http_test [num] [host] [port]!\n");
		exit(-1);
	}
	int num =  atoi(argv[1]);
	pthread_t* rtid = calloc(num, sizeof(pthread_t));
	pthread_t* stid = calloc(num, sizeof(pthread_t));
	int i = 0;
	int port = atoi(argv[3]);
	struct sockaddr_in addr;  //定义一个IP地址结构
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;  //将addr结构的属性定位为TCP/IP地址
	addr.sin_port = htons(port);    
	addr.sin_addr.s_addr = inet_addr(argv[2]);
	int st = 0;
	int on = 1;
	while(i < num)
	{
		st = socket(AF_INET, SOCK_STREAM, 0);   //初始化socket
		on = 1;
		if(setsockopt(st, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
		{
			return EXIT_FAILURE;
		}
		
		if(connect(st, (struct sockaddr*)&addr, sizeof(addr) ) == -1)
		{
			return EXIT_FAILURE;
		}
		pthread_create(&(rtid[i]), NULL, http_send, (void*)&st);
		pthread_create(&(stid[i]), NULL, http_recv, (void*)&st);
		++i;
	}
	for(i = 0; i < num; ++i)
	{
		pthread_join(rtid[i], NULL);
		pthread_join(stid[i], NULL);
	}
	return 0;
}
