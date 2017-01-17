/**
 *  Filename: cpu_set.c
 *   Created: 2016-07-13 17:44:18
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <pthread.h>
void* test_func(void* arg)
{
    cpu_set_t cpus;
    int sched_num = 0;
    CPU_ZERO(&cpus);
    sched_getaffinity(0, sizeof(cpu_set_t), &cpus);
    sched_num = CPU_COUNT(&cpus);
    printf("sched_num: %d\n", sched_num);
    CPU_ZERO(&cpus);
    CPU_SET(1, &cpus);
    /* CPU_ZERO(&cpus); */
    sched_getaffinity(0, sizeof(cpu_set_t), &cpus);
    sched_num = CPU_COUNT(&cpus);
    printf("sched_num: %d\n", sched_num);
    while(1)
    {

    }
    return NULL;
}
int main(int argc, char* argv[])
{
    pthread_t app_thread;
    pthread_create(&app_thread, NULL, test_func, NULL);
    while(1)
    {

    }
    return 0;
}
