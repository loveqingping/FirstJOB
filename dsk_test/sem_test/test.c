/**
 *  Filename: test.c
 *   Created: 2016-05-04 16:10:56
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t sem;
sem_t sem2;
void* func1(void* arg)
{
    int i = (int)arg;
    /* sem_wait(&sem); */
    printf("func1:%d\n", i);
    return NULL;
}
void* func2(void* arg)
{
    int i = (int)arg;
    sem_post(&sem);
    sem_post(&sem2);
    printf("func2:%d\n", i);
    return NULL;
}
int main(int argc, char* argv[])
{
    sem_init(&sem, 0, 0);
    sem_init(&sem2, 0, 0);
    pthread_t tid;
    pthread_create(&tid, NULL, func1, (void*)1);
    pthread_create(&tid, NULL, func2, (void*)2);
    sem_wait(&sem2);
    int val;
    sem_getvalue(&sem, &val);
    printf("val:%d\n", val);
    while(1)
    {

    }
}
