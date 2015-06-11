
#ifndef __BINDER_H__
#define __BINDER_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BINDER_SERVICE_MANAGER 0

#define SVC_MGR_ADD_SERVICE 	0xFFFFFFF0
#define SVC_MGR_CHECK_SERVICE   0xFFFFFFF1

#define BINDER_PATH		"/tmp/binder"

bool server_init = false;
bool client_init = false;


int binder_open(int mapsize)
{
	return rand() % 100;
}

int create_pipe(const char* path, int mode)
{
	int ret = mkfifo(path, 0600);
	if (ret < 0 && errno != EEXIST)
	{
		perror("mkfifo");
		exit(-1);
	}

	int fd = open(path, mode);
	if(fd < 0)
	{
		perror("open");
		exit(-1);
	}

	return fd;
}

int binder_fd = 0;
const char* service_name;
int binder_call(int binder, int* msg, int* reply, int target, int code)
{
	if (code == SVC_MGR_ADD_SERVICE)
	{
		if (server_init == false)
		{
			service_name = reinterpret_cast<const char*>(msg);
			server_init = true;
			binder_fd = create_pipe(BINDER_PATH, O_RDWR);
		}
		return 0;
	}
	else if (code == SVC_MGR_CHECK_SERVICE)
	{
		if (client_init == false)
		{
			client_init = true;
			binder_fd = create_pipe(BINDER_PATH, O_WRONLY);
		}
		return -1;
	}

	if (client_init == false)
		return -1;

	int rpc_code = code;
	return write(binder_fd, &rpc_code, sizeof(int));
}

typedef int(*binder_handler)(int code, int msg, int* reply);
void binder_loop(int binder, binder_handler func)
{
	printf("[%s] running...\n", service_name);
	int msg, reply;
	int readn, rpc_code;
	while (true)
	{
		readn = read(binder_fd, &rpc_code, sizeof(int));
		func(rpc_code, msg, &reply);
	}
}

#endif
