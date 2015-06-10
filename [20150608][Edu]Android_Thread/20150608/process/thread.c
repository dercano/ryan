
// thread.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                    void *(*start_routine) (void *), void *arg); 
void* thread_func(void* arg) {
	const char* name = (const char* )arg;
	int i;
	for(i = 0; i < 10; i++) {
		printf("\t%s\n", name);
		sleep(1);
	}
	printf("\texit %s\n", name);
	return NULL;
}

int main() {
	pthread_t tid;
	pthread_create(&tid, 0, thread_func, "Worker Thread");	// 3 + K

	while(1) {
		printf(".\n");
		sleep(1);
	}
	return 0;
}
