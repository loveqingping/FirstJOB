#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define rb_create(puf,num) \
	(puf = malloc(sizeof(int) * num),puf)
int main(int argc, char* argv[])
{
	int* p = NULL;
	p = rb_create(p,4);
	if(p != NULL)
	{
		p[1] = 1;
		p[2] = 2;
		printf("p[1]:%d\n",p[1]);
	}
	int i = 0;
	for(i = 0; i < 10,i == -1;++i)
	{

	}
	printf("i = %d\n",i);
	return 0;
}
