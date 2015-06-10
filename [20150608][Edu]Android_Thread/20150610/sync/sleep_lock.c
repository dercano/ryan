
// sleep_lock.c

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int sum = 0;
void* thread_func(void* arg) {
	int i;
	for(i = 0; i < 100000000; i++) {
		pthread_mutex_lock(&mutex);
		//--------------------------
		++sum; sleep(60);
		//--------------------------
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main() {
	pthread_t t1, t2;
	pthread_create(&t1, 0, thread_func, 0);
	pthread_create(&t2, 0, thread_func, 0);
	pthread_join(t1, 0);
	pthread_join(t2, 0);

	printf("sum = %d\n", sum);
	return 0;
}
