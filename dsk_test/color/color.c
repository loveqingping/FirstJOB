#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc,char* argv[])
{
    fprintf(stderr, "[\033[1;40;33mWARN\033[m](%s:%d)\n",__FILE__,__LINE__);
    fprintf(stderr, "[\033[40;33mWARN\033[m](%s:%d)\n",__FILE__,__LINE__);
    fprintf(stderr, "\033[41;32m字体背景是红色，字是绿色\033[0m\n");
    return 0;
}
