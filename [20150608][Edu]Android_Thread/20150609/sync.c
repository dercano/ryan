
// sync.c
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int sum = 0;
void* thread_func(void* arg) {
	int i;
	for(i = 0; i < 10000000; i++) {
		pthread_mutex_lock(&mtx);
		//-------------------------
		++sum;	// 원자적 연산(atomic operation, 연산이 더 이상 분해되지 않음)
		//-------------------------
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

int main() {
	int i;
	pthread_t tid[2];
	for(i = 0; i < 2; i++)
		pthread_create(&tid[i], 0, thread_func, 0);

	for(i = 0; i < 2; i++)
		pthread_join(tid[i], NULL);

	printf("sum = %d\n", sum);
	return 0;
}


