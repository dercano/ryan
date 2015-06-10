
// process.c
#include <stdio.h>
#include <unistd.h>

// 새로운 프로세스 생성
int main()
{
	pid_t pid = fork();

	if(pid > 0) {	// parent process
		printf("[parent] hello\n");
	}
	else if(pid == 0) {	// child process(new process)
		printf("[child] hello\n");
	}
	else {	// error
		perror("fork");
		return -1;
	}
	return 0;
}
