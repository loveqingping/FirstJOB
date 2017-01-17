#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include "nbk_iconv.h"
#include <memory.h>
#define MAX (10*1024)
int main(int argc ,char* argv[])
{
	FILE* fp = fopen(argv[1],"r+");
	char buf[10*1024];
	char temp[20*1024];
	memset(temp,0,sizeof(temp));
	memset(buf,0,sizeof(buf));
	int nread = 0;
	int size = 0;
	if(fp == NULL)
	{
		fprintf(stderr,"fopen error %s:%d",__func__,__LINE__);
		return -1;
	}
	while(1)
	{
		nread = fread(buf+size,sizeof(char),MAX,fp);
		size = size + nread;
		if(nread < MAX)
		{
			break;
		}
	}
	if(1 == is_gb2312(buf,size) )
	{
		fprintf(stdout,"The file 's code is GB2312\n");
		g2u(buf,size,temp,sizeof(temp));
		printf("buf:%s",temp);
	}
	else
	{
		fprintf(stdout,"The file 's code isn't GB2312\n");
	}
	return 0;
}
