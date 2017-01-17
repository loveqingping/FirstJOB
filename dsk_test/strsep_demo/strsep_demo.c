/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc ,char *args[])
{
    char str[]={"hello world"};
    char *tmp = str;
    char *res = strsep(&tmp," ");
    printf("res = %s\n",res);
	printf("tmp = %s\n",tmp);    
    return 0;
}

