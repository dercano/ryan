
// futex.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h> 

// __futex_wait

int mutex = 1;	// locked!
void* thread_func(void* arg) {
	printf("[worker] sleep...\n");
	syscall(202, &mutex, 0, 1, 0);	// futex_wait();
	printf("[worker] wake!\n");
	return NULL;
}

int main() {
	pthread_t tid;
	pthread_create(&tid, 0, thread_func, 0);

	getchar();
	syscall(202, &mutex, 1, 1);		// futex_wake();

	pthread_join(tid, 0);
	return 0;
}
