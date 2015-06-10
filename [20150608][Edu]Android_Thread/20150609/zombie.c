
#if 0
// zombie.c
#include <stdio.h>
#include <unistd.h>

// ESC -> : -> tj task_struct

int main()
{
	if(fork() == 0) {	// child process
		int i;
		for(i = 0; i < 5; i++) {
			printf("\t[child] do something\n");
			sleep(1);
		}
		printf("\t[child] terminated\n");
		return 0;
	}

	// parent process
	while(1) {
		printf("[parent] do something\n");
		sleep(1);
	}
	return 0;
}

#endif

#if 0

// 좀비 프로세스의 문제는 해결했지만 비동기적으로 수행되지 않음 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	if(fork() == 0) {	// child process
		int i;
		for(i = 0; i < 5; i++) {
			printf("\t[child] do something\n");
			sleep(1);
		}
		printf("\t[child] terminated\n");
		return 7;	// 리턴 값이 바로 종료 코드
	}

	int exit_code;
	wait(&exit_code);
	printf("[parent] exit code = %d\n", WEXITSTATUS(exit_code));	// exit_code);

	// parent process
	while(1) {
		printf("[parent] do something\n");
		sleep(1);
	}
	return 0;
}


#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_handler(int signo) {
	int exit_code;
	wait(&exit_code);
	printf("[parent] exit code = %d\n", WEXITSTATUS(exit_code));	// exit_code);
}

int main() {
	signal(SIGCHLD, sig_handler);	// 2 + K
	if(fork() == 0) {	// child process
		int i;
		for(i = 0; i < 5; i++) {
			printf("\t[child] do something\n");
			sleep(1);
		}
		printf("\t[child] terminated\n");
		return 7;	// 리턴 값이 바로 종료 코드
	}
	while(1) {
		printf("[parent] do something\n");
		sleep(1);
	}
	return 0;
}


