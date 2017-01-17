#include <stdio.h>
int test(int a, int b)
{
	a = 3;
	b = 4;
	return a + b;
}
int main(int argc, char* argv[])
{
	int a = 1;
	int b = 2;
	test(1, 2);
	return 0;
}

