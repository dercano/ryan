
// servier.cpp
#include "Android.h"

int my_handler(int code, int msg, int* reply)
{
	switch (code)
	{
		case 1: printf("LED ON\n"); break;
		case 2: printf("LED OFF\n"); break;
	}
	return 0;
}

int main(int argc, const char *argv[])
{
	// 1. open binder
	int fd = binder_open(128*1024);

	// 2. add service
	int reply;
	binder_call(fd, (int*)"LedService", &reply,
			BINDER_SERVICE_MANAGER, SVC_MGR_ADD_SERVICE);

	// 3. wait request
	binder_loop(fd, my_handler);
	return 0;
}










