#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
int main(int argc, char* argv[])
{
		int *p = (int*)malloc(sizeof(int) * 1024);
		int i = 0;
		while(1)
		{
			p[i] = i;
			i = (i + 1)%1024;
			fprintf("p[i]:%d\n",p[i]);
		}
}
