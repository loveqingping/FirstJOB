#include <stdio.h>
#include <stdlib.h>
#include <vshell.h>
#include <pthread.h>
#include <stdarg.h>
void* thr_func(void* arg)
{
	vshell_start("0.0.0.0", 12306);
	pthread_exit(NULL);
}
void show_status(void* session, int argc, char** argv, char* raw)
{
	vshell_printf(session,"hahahahahahahah\n");
}
#if 0
int nbk_http_vshell_register(void* parent, vshell_cmd_func cmd_func, int argc, char* cmd1, ...)
{
	void* cmd;
	if(parent == cmd_root)    //表明从根命令开始注册
	{
		cmd = vshell_register_cmd(parent, cmd1, cmd1, NULL); //先将第一级命令注册
	}
	char* p;
	va_list ptr;
	va_start(ptr, cmd1);    //ptr指向后一个参数, 也就是第二级命令
	int i = 0;
	for(i = 0; i < argc - 1; ++i)
	{
		p  = va_arg(ptr,char*);
		if( i == argc - 2)
		{
			cmd = vshell_register_cmd(cmd, p, p, cmd_func);
		}
		else
		{
			cmd = vshell_register_cmd(cmd,p, p ,NULL);
		}
	}
	return 0;
}
#endif
int main()
{
	void* cmd1;
	void* cmd2;
	pthread_t tid;
	vshell_init();
	vshell_set_prompt("test");
	//cmd1 = vshell_register_cmd(cmd_root,"show","hsow demo",NULL);
	//cmd2 = vshell_register_cmd(cmd1, "status","show status",show_status);
	nbk_http_vshell_register(cmd_root, show_status, 3, "show", "http", "status");
	nbk_http_vshell_register(cmd_root, show_status, 2, "http", "haha", "status");
	pthread_create(&tid,NULL,thr_func,NULL);
	while(1)
	{

	}
	return 0;
}

