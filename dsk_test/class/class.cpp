/**
 *  Filename: class.cpp
 *   Created: 2016-08-18 12:57:57
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <iostream>
#include <stdio.h>
class B
{
public:
    void func()
    {
        printf("hello!\n");
    }
private:
};
class A
{
public:
    void func()
    {
        num++;
    }
private:
    int num;
};
class C
{
public:
    virtual void func()
    {
        printf("hello \n");
    }
};
// int A::num = 0;
int main(int argc, char* argv[])
{
    // A* p = NULL;
    B* p2 = NULL;
    C* p3 = NULL;
    // p->func();
    p2->func();
    p3->func();
    return 0;
}
