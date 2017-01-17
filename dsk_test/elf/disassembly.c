/**
 *  Filename: disassembly.c
 *   Created: 2016-01-27 09:23:10
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
char* str = "Hello world!\n";
void print()
{
    asm("movl $13, %%edx\n\t"
        "movl %0, %%ecx\n\t"
        "movl $1, %%ebx \n\t"
        "movl $4, %%eax \n\t"
        "int $0x80 \n\t"
        ::"r"(str):"edx", "ecx", "ebx");
}
void exit()
{
    asm("movl $42, %ebx \n\t"
        "movl $1, %eax \n\t"
        "int $0x80      \n\t");
}
void nomain()
{
    print();
    exit();
}
