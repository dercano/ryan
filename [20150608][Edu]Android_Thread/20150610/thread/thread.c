
// thread.c

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void* thread_func(void* arg) {
	int i=0;
	for(i=0; i<5; i++) {
		printf("\tWorker Thread\n");
		sleep(1);
	}
	return NULL;
}

int main() {
	pthread_t tid;
	pthread_create(&tid, 0, thread_func, 0);
	getchar();
}
