/**
 *  Filename: build_cpu.c
 *   Created: 2014-07-11 17:02:39
 *      Desc: TODO (some description)
 *    Author: xutao(Tony Xu), xu.tao@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define __USE_GNU
#include <sched.h>
#include <pthread.h>

void *t_fun(void *arg)
{
    cpu_set_t mask;
    int cpuid = *(int *)arg;
    CPU_ZERO(&mask);
    CPU_SET(cpuid, &mask);

    if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {
        printf("warning: could not set CPU affinity, continuing...\n");
    }
    while (1) {
        usleep(10);
        fprintf(stderr, "test CPU NO.%d\n", cpuid);
    }
    pthread_exit((void *)0);
}

int main(int argc, char *argv[])
{
    pthread_t tid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s cpuid\n", argv[0]);
        exit(1);
    }

    int cpuid = (int)strtol(argv[1], NULL, 10);

    pthread_create(&tid, NULL, (void *)t_fun, &cpuid);

    pthread_join(tid, NULL);

    return 0;
}
