
#if 0
// process.c
#include <stdio.h>
#include <unistd.h>

int main()
{
	fork();	// CreateProcess(,,,,,,); in Window$
	printf("hello, world\n");
	return 0;
}
#endif

// process.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid = fork();

	if(pid > 0)	{
		printf("[parent] hello, world\n");
	} else if(pid == 0) {
		printf("[child] hello, world\n");
	} else {
		perror("fork");
		exit(-1);	// 3 + K
	}

	return 0;
}















