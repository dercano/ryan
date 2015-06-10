
// 2.c
// 임계 영역(critial section)
#include <stdio.h>
#include <pthread.h>

int flag = 0;
int sum = 0;
void* thread_func(void* arg) {
	int i;
	for(i = 0; i < 100000000; i++) {
		while(flag);
		flag = 1;
		//--------------------------
		++sum;
		//--------------------------
		flag = 0;
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
