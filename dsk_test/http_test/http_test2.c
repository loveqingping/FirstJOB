/**
 *  Filename: http_test2.c
 *   Created: 2015-10-15 18:26:47
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo), du.shangkun@ampthon.com
 *   Company: Ampthon
 */
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
int main(int argc, char* argv[])
{
    if(argc < 3)
	{
		fprintf(stderr,"Usage http_test  [host] [port]!\n");
		exit(-1);
	}
    int port = atoi(argv[2]);
	struct sockaddr_in addr;  //定义一个IP地址结构
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;  //将addr结构的属性定位为TCP/IP地址
	addr.sin_port = htons(port);    
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	int st = 0;
	int on = 1;
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
#if 0
        char* request = "GET / HTTP/1.0\r\nHost: www.kun.com\r\nUser-Agent: ApacheBench/2.3\r\nAccept: */*\r\n\r\n";
        char req[2048];
        bzero(req, 2048);
        strncpy(req, request, strlen(request));
        send(st, req, strlen(req), 0);

#endif
        char buf[2048];
        int ret = 0;
        while(1)
        {
#if 0
            bzero(buf, 2048);
            ret = recv(st, buf, 2048, 0);
            if(ret <= 0)
            {
                break;
            }
            fprintf(stderr, "ret = %d\n", ret);
#endif
            sleep(1);
        }
}

