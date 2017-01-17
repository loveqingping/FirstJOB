#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int hex2dec(char ch)
{
	char ch2;
	if( (ch >= '0')&&(ch <= '9'))
	{
		return (int)(ch - '0');
	}
	ch2 = toupper(ch);
	if((ch2 >= 'A') && (ch2 <= 'F') )
	{
		return (int)(10 + (ch2 - 'A'));
	}
	return -1;
}
int main(int argc,char* argv[])
{
	char* p = argv[1];
	int val = 0;
	while(1)
	{
		if(isxdigit(*p))
		{
			val = val * 16;
			val = val + hex2dec(*p);
		}
		else
		{
			break;
		}
		++p;
	}
	printf("val =  %d\n",val);
	return 0;
}
