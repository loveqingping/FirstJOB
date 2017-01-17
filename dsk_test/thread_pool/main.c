#include <thread_pool.h>
#include <stdio.h>
typedef struct student
{
	int id;
	char name[64];
}student;
void* test_func(void* arg)
{
	student xiaoming = *((student*)arg);
	printf("ID:%d name:%s\n",xiaoming.id,xiaoming.name);
	return NULL;
}
int main(int argc, char* argv[])
{

	student st;
	int i = 0;
	thread_pool_create(10,10);
	for(i = 0; i < 5; ++i)
	{
		st.id = i;
		sprintf(st.name,"No.%d",i);
		thread_pool_add_task(test_func,&st);
	}
	while(1)
	{

	}
	return 0;
}
