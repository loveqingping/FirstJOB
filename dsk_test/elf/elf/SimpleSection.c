/**
 *  Filename: SimpleSection.c
 *   Created: 2015-11-15 14:17:17
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo), du.shangkun@ampthon.com
 *   Company: Ampthon
 */
int printf(const char* format, ...);
int global_init_var = 84;  //data segment
int global_uninit_var;     //bss segment
void func1(int i)
{
    printf("%d\n", i);
}
int main(void)
{
    static int static_var = 85;   //data segment
    static int static_var2;      //bss segment
    int a = 1;
    int b;
    func1(static_var + static_var2 + a + b);
    return a;
}
