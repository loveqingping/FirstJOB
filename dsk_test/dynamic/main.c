/**
 *  Filename: main.c
 *   Created: 2016-07-26 16:42:06
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include "test.h"
#include <stdio.h>
#include <dlfcn.h>
typedef int (*func)();
int main(int argc, char* argv[])
{
    printf("exe!\n");
    test();
    func f1;
    char* err = NULL;
    void* handle = dlopen("libshare.so", RTLD_LAZY);
    err = dlerror();
    printf("err :%s\n", err);

    f1 = dlsym(handle, "share");
    f1();
    return 0;
}
