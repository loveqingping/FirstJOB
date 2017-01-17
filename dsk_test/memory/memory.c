#include <stdio.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	int i = 0;
	int* p = &i;
	char c = 48;
	int *p1 = &c;
	printf("%p\n",p);
	printf("%p\n",p1);
	return 0;
}
