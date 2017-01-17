/**
 *  Filename: str_loop_mov.c
 *   Created: 2016-03-09 09:01:50
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int str_loop_mov(char* str, int step, char* new_str)
{
    char buf[1024];
    bzero(buf, sizeof(buf));
    int src_len = strlen(str);
    int i = src_len - 1;
    for(; i >= 0; --i)
    {
       buf[ (i+step)%src_len]  = str[i];
    }
    strncpy(new_str, buf, src_len);
    return 0;
}
int main(int argc, char* argv[])
{
    char str[] = "abcdef";
    char buf[1024];
    bzero(buf, sizeof(buf));
    str_loop_mov(str, 3, buf);
    printf("%s\n", buf);
    return 0;
}
