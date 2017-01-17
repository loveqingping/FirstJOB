#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
int main(int argc,char* argv[])
{
	int d = 0;
	char*p = argv[1];
	sscanf(p,"%x",&d);
	printf("%d\n",d);
	return 0;
}
