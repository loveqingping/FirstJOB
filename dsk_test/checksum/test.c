#include <stdio.h>
#include <stdlib.h>
int main(int argc ,char* argv[])
{
	int a = -1;
	printf("a = %x\n",a);
	int b = ~a;
	printf("b = %x\n",b);
	return 0;
}
