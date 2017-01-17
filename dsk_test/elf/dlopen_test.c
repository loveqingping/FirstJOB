#include <dlfcn.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	void* libc;
	void (*printf_call)();
	char* error_text;
	if(libc = dlopen("/lib64/libc.so.6", RTLD_LAZY))
	{
		printf_call = dlsym(libc, "printf");
		printf_call("hello world\n");
		dlclose(libc);
		return 0;
	}
	error_text = dlerror();
	printf(error_text);
	return -2;
}
