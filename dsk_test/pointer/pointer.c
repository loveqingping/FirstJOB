/**
 *  Filename: pointer.c
 *   Created: 2016-04-19 09:48:08
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
#include <stdint.h>
int main(int argc, char* argv[])
{
    int a[10];
    int* p1 = &a[0];
    int* p2 = &a[1];
    if(p1 < p2)
    {
        printf("hahahahahah!\n");
    }
    return 0;
}
