/**
 *  Filename: test.c
 *   Created: 2015-11-18 15:47:34
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo), du.shangkun@ampthon.com
 *   Company: Ampthon
 */
#include <stdio.h>
#include <stdlib.h>
void func1()
{
    int i = 0, j;
    for(j = 0; j < 10000; j++)
    {
        i+=j;
    }
}
void func2()
{
    int i, j;
    func1();
    for(j = 0; j < 20000; j++)
    {
        i = j;
    }
}
int main()
{
    int i, j;
    for(i = 0; i < 100; i++)
    {
        func1();
    }
    for(j = 0; j < 50000; j++)
    {
        func2();
    }
    return 0;
}
