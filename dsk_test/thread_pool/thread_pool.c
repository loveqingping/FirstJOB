#include "thread_pool.h"
#include "ring_buffer.h"
static int task_dequeue(task_t* p_task)
{

	if(1 == rb_canRead(thread_pool.task) )
	{
		*p_task = rb_readPeek(thread_pool.task,task_t);
		rb_readOut(thread_pool.task);
		return 0;
	}
	else
	{
		return -1;
	}
}
static void* thread_pool_exec(void* arg)    //有点问题这里
{
	task_t tmp_task;
	while(1)
	{	
		pthread_mutex_lock(&(thread_pool.mutex));
		if(0 == task_dequeue(&tmp_task) )  //任务出队成功
		{			
#ifdef DEBUG 0
			fprintf(stderr,"LWP(%d):process\n",getpid());
#endif
			thread_pool.cur_task_num--;
			tmp_task.task_func(tmp_task.arg);       //执行任务
			pthread_mutex_unlock(&thread_pool.mutex);   //执行完任务之后，释放锁
		}
		else
		{
			pthread_cond_wait(&(thread_pool.cond),&(thread_pool.mutex));  //任务出队失败，那么就会进入睡眠
			pthread_mutex_unlock(&thread_pool.mutex);
		}
		pthread_testcancel();

	}
	return NULL;
}
int thread_pool_create(int thread_num, int max_task_num)
{
	if(thread_num > MAX_THREAD_NUM || thread_num < 1)
	{
		fprintf(stderr,"thread_num error!\n");
		return -1;
	}
	/*
	if(task_num > MAX_TASK_NUM || task_num < 0)
	{
		fprintf(stderr,"task_num error!\n");
		return -1;
	}
	*/
	task_t* p_task = NULL;
	int i = 0;
	p_task = rb_create(max_task_num,sizeof(task_t),p_task);
	if(p_task == NULL)
	{
		fprintf(stderr,"ring_buffer create failed!\n");
		return -1;
	}
	thread_pool.max_task_num = max_task_num;
	thread_pool.cur_task_num = 0;
	thread_pool.task = p_task;
	thread_pool.thread_num = thread_num;
	pthread_mutex_init(&(thread_pool.mutex),NULL);  //初始化互斥锁
	pthread_cond_init(&(thread_pool.cond),NULL);
	/*线程启动*/
	for(i = 0;i < thread_num;++i)
	{
		pthread_create(&(thread_pool.thread[i]),NULL,thread_pool_exec,NULL);
	}
	return 0;
}
static int task_enqueue(task_func_t user_task_func,task_func_arg user_arg)
{
	if(1 == rb_canWrite(thread_pool.task) )
	{
		rb_writePeek(thread_pool.task,task_t).task_func = user_task_func;
		rb_writePeek(thread_pool.task,task_t).arg = user_arg;
		rb_writeIn(thread_pool.task);
		return 0;
	}
	else
	{
		return -1;
	}

}
int thread_pool_add_task(task_func_t user_task_func,task_func_arg user_arg)
{
	pthread_mutex_lock(&(thread_pool.mutex) );
	if(0 == task_enqueue(user_task_func, user_arg) )  //	
	{
		thread_pool.cur_task_num++;
		pthread_mutex_unlock(&(thread_pool.mutex));
		pthread_cond_signal(&(thread_pool.cond));   //通知睡眠的线程
		return 0;
	}
	else
	{
		pthread_mutex_unlock(&(thread_pool.mutex));
		return -1;
	}
}
int thread_pool_stop_all()
{
	int i = 0;
	for(i = 0;i < thread_pool.thread_num; ++i)
	{
		pthread_cancel(thread_pool.thread[i]);
	}
	return 0;
}
int thread_pool_destroy()
{
	if(thread_pool.task != NULL)
	{
		free(thread_pool.task);  //销毁任务队列
		thread_pool.task = NULL;
	}
	pthread_mutex_destroy(&thread_pool.mutex);
	pthread_cond_destroy(&thread_pool.cond);
	return 0;
}
