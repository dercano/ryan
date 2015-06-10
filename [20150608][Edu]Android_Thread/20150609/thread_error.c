

#if 0
#include <stdio.h>
#include <pthread.h>
#include <string.h>

int main()
{
	pthread_t tid;
	int ret = pthread_join(tid, NULL);	// 에러 발생
	if(ret != 0)
	{
		fprintf(stderr, "pthread_join: %s\n", strerror(ret));
		// perror("pthread_join");
		return -1;
	}
	return 0;
}
// 스레드 라이브러리는 errno 를 사용하지 않습니다.
#endif

#if 1
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// 함수 호출의 오버헤드 존재
/*
void err_abort(int status) {
	fprintf(stderr, "%s\n", strerror(status));
	abort();	// exit(-1);
}
*/

#define err_abort(status) 						\
do {											\
	fprintf(stderr, "%s\n", strerror(status)); 	\
	abort();									\
} while(0)

int main()
{
	pthread_t tid;
	int ret = pthread_join(tid, NULL);	// 에러 발생
	if(ret != 0)
		err_abort(ret);
	else
		printf("KKK\n");

	return 0;
}
#endif













#if 0
#include <stdio.h>
#include <pthread.h>

// 두 개 이상의 쓰레드가 하나의 공유 자원에 접근할 경우, 경합이 벌어지고
// 연산이 원자적으로 수행되지 않아 값이 정상적으로 처리되지 않습니다.
int errno = 0;	// global is evil
void* thread_func(void* arg) {
	int i;
	for(i = 0; i < 100000; i++)
		//--------------------
		errno++;
	//--------------------
	return NULL;
}

int main() {
	pthread_t tid[2];

	pthread_create(&tid[0], 0, thread_func, 0);
	pthread_create(&tid[1], 0, thread_func, 0);

	pthread_join(tid[0], 0);
	pthread_join(tid[1], 0);

	printf("errno = %d\n", errno);
	return 0;
}
#endif









