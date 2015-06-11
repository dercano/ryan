
// client.cpp
#include "Android.h"

int main(int argc, const char *argv[])
{
	int fd = binder_open(128*1024);

	int msg, reply;
	int handle = binder_call(fd, (int*)"LedService", &reply,
			BINDER_SERVICE_MANAGER,	SVC_MGR_CHECK_SERVICE);

	while (1)
	{
		getchar(); binder_call(fd, &msg, &reply, handle, 1);
		getchar(); binder_call(fd, &msg, &reply, handle, 2);
	}

	return 0;
}
