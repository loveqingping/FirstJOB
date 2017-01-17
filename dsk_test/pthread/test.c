/**
 *  Filename: test.c
 *   Created: 2016-07-12 09:58:00
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void* thread_func(void* arg)
{
    while(1)
    {
        printf("hahahahaha!\n");
        sleep(10);
    }
}
void thread_run(int thr_id)
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
}
int main(int argc, char* argv[])
{
    thread_run(0);
    printf("run-------------!\n");
    /* return 0; */
    pthread_exit(NULL);
}
