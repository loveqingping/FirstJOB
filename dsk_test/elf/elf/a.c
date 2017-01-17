/**
 *  Filename: a.c
 *   Created: 2015-11-19 14:54:23
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo), du.shangkun@ampthon.com
 *   Company: Ampthon
 */
extern int shared;
int main()
{
    int a = 100;
    swap(&a, &shared);
}
