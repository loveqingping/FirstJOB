/**
 *  Filename: test.c
 *   Created: 2016-05-03 15:41:32
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    /*  当多个定界符连续出现时，strtok/strtok_r函数认为只有一个， 如下面的
     *  \t= , 在循环输出时根本不会输出"="
     */
    char str[] = "port  = 80";
    char* ptr = NULL;
    char* save_ptr = NULL;
    ptr = strtok_r(str, "\t=", &save_ptr);
    printf("%s\n", ptr);
    while( (ptr = strtok_r(NULL, "\t=", &save_ptr)) != NULL)
    {
        printf("%s\n", ptr);
    }
    return 0;
}
