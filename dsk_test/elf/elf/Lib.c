/**
 *  Filename: Lib.c
 *   Created: 2015-11-23 09:48:48
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo), du.shangkun@ampthon.com
 *   Company: Ampthon
 */
#include <stdio.h>
extern void ext();
void foobar(int i)
{
    printf("Printing from Lib.so %d\n", i);
    ext();
    sleep(-1);
}
