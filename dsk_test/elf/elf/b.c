/**
 *  Filename: b.c
 *   Created: 2015-11-19 14:55:19
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo), du.shangkun@ampthon.com
 *   Company: Ampthon
 */
int shared = 1;

void swap(int *a, int *b)
{
    *a ^= *b ^= *a ^= *b;
}
