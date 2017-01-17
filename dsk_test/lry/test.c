/**
 *  Filename: test.c
 *   Created: 2016-03-18 12:48:26
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
/*
 *计算字符串的长度
 *C语言中字符串以'\0'结尾
 *加const是为防止对str做修改，表示str是只读，不能修改
 */
int mystrlen(const char* str)
{
    if(str == NULL)   //对str的有效性做判断
    {
        return -1;
    }
    int len = 0;   // 将len初始化为0
    char* p = (char*)str;
    while(*p != '\0')
    {
        p++;
        len++;
    }
    return len;
}
/*
 *统计数字串中的奇数个数
 *
 *
 */
int sum_odd(const char* str)
{
    if(str == NULL)    //对str的有效性做判断
    {
        return -1;
    }
    int count = 0;
    int temp;        //用来保存字符转换为整数之后的值,方便进行模运算
    char* p = (char*)str;
    while(*p != '\0')
    {
        temp = *p - '0';
        if(temp %2 != 0)
        {
            count++;
        }
        p++;
    }
    return count;
}
/*
 *统计数字串中的偶数个数
 *
 *
 */
int sum_even(const char* str)
{
    if(str == NULL)    //对str的有效性做判断
    {
        return -1;
    }
    int count = 0;
    int temp;        //用来保存字符转换为整数之后的值,方便进行模运算
    char* p = (char*)str;
    while(*p != '\0')
    {
        temp = *p - '0';
        if(temp %2 == 0)
        {
            count++;
        }
        p++;
    }
    return count;
}
void init_buf(char* buf, int len)
{
    if(buf == NULL)
    {
        return;
    }
    char* p = buf;
    int i = 0;
    while( i < len)
    {
        *p = '\0';
        p++;
        i++;
    }
}
void get_magic_num(const char* str)
{
    if(str == NULL)
    {
        printf("str == NULL!\n");
        return ;
    }
    char* p = (char*)str;
    int pre_a = 0;   //pre_a, pre_b, pre_c分别保存上次计算出来的值
    int pre_b = 0;
    int pre_c = 0;
    int cur_a = 0;
    int cur_b = 0;
    int cur_c = 0;
    char buf[1024];
    while(1)
    {
        cur_a = mystrlen(p);
        cur_b = sum_odd(p);
        cur_c = sum_even(p);
        if( (cur_a == pre_a) && (cur_b == pre_b) && (cur_c == pre_c) ) //循环结束条件
        {
            break;
        }
        init_buf(buf, 1024);      //清空缓冲区，避免被干扰
        snprintf(buf, 1024, "%d%d%d", cur_a, cur_b, cur_c);  //根据abc的值，再生成字符串
        p = buf;          //p指向新生成的数字串
        pre_a = cur_a;
        pre_b = cur_b;
        pre_c = cur_c;
    }
    printf("magic_num:%s\n", buf);
}
int main(int argc, char* argv[])
{
    get_magic_num(argv[1]);
    return 0;
}

