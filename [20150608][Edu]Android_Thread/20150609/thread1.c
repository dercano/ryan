
// thread1.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_func(void* arg) {
	const char* name = (const char* )arg;

	int i;
	for(i = 0; i < 5; i++) {
		printf("\t%s\n", name);
		sleep(1);
	}
	printf("\texit %s\n", name);
	return NULL;
}

int main() {
	pthread_t tid;
	pthread_create(&tid, 0, thread_func, "Worker Thread");

	while(1) {
		printf("Main Thread\n");
		sleep(1);
	}
	pthread_join(tid, 0);
	return 0;
}
