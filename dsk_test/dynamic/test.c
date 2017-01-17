/**
 *  Filename: test.c
 *   Created: 2016-07-26 16:35:45
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
int a = 1;
int test(int argc, char* argv[])
{
    printf("I am static library!\n");
    printf("a:%p\n", &a);
    return 0;
}
