#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <pthread.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX_THREAD_NUM 256
#define DEBUG 0
typedef void* (*task_func_t)(void*);
typedef void* task_func_arg;
typedef struct _task
{
	task_func_t task_func;
	task_func_arg arg;
}task_t;
typedef struct _thread_pool
{
	pthread_t thread[MAX_THREAD_NUM];  //用来存放线程ID;
	task_t* task;
	uint32_t cur_task_num;
	uint32_t max_task_num;                //存放最大任务数量
	uint32_t thread_num;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}thread_pool_t;
thread_pool_t thread_pool;
int thread_pool_create(int thread_num, int task_num);
int thread_pool_add_task(task_func_t user_task_func, task_func_arg user_arg);
int thread_pool_stop_all();
int thread_destroy();
#endif
