
#if 0
// memory_model.c
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

// 1. process
int global = 0;

int main() {
	if(fork() == 0) {	// in child process
		global++;
		printf("[child] global = %d\n", global);
		return 0;
	}

	wait(0);
	printf("[parent] global = %d\n", global);
	return 0;
}
#endif



#include <pthread.h>
#include <stdio.h>

int global = 0;
void* thread_func(void* arg) {
	int* p = (int*)arg;
	global++;	// 전역 변수
	++(*p);		// 지역 변수
	printf("[worker] global = %d\n", global);
	printf("[worker] local = %d\n", *p);
	return NULL;
}

int main() {
	int local = 0;

	pthread_t tid;
	pthread_create(&tid, 0, thread_func, &local);
	pthread_join(tid, 0);

	printf("[main] global = %d\n", global);
	printf("[main] local = %d\n", local);
	return 0;
}























