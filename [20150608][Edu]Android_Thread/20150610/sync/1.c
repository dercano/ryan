

// 1.c
// 임계 영역(critial section)
#include <stdio.h>
#include <pthread.h>

int sum = 0;
void* thread_func(void* arg) {
	int i;
	for(i = 0; i < 100000000; i++) {
		//--------------------------
		++sum;	// ++ 원자적 연산이 아님, ++ 연산은 하나이지만 기계어 코드는 2개 이상의 연산자로 생성됨
		//--------------------------
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
