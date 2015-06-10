
#if 0
// thread.c
#include <stdio.h>
#include <unistd.h>

void* print(void* arg) {
	const char* p = (const char*)arg;
	int i;
	for(i = 0; i < 5; i++) {
		printf("%s\n", p);
		sleep(1);
	}
}

// 메인 함수를 호출한 스레드를 메인 스레드 또는 주 스레드라고 합니다
// 프로세스는 기본적으로 단일 스레드로 실행됩니다. 이 때, 스레드의 기본
// 실행 단위는 함수이며 때문에 단일 스레드에서는 함수가 직렬적(동기적)으로
// 수행되빈다.
int main()
{
	print("\tdo something");
	while(1) {
		printf("main thread\n");
		sleep(1);
	}
	return 0;
}

#endif

#if 0
// thread.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_func(void* arg) {
	const char* p = (const char*)arg;
	int i;
	for(i = 0; i < 5; i++) {
		printf("%s\n", p);
		sleep(1);
	}
	return NULL;
}

// 스레드 코드를 빌드할 경우, -lpthread 옵션을 사용해야 합니다
int main()
{
	pthread_t tid;
	pthread_create(&tid, 0, thread_func, "\tWorker Thread");

	while(1) {
		printf("main thread\n");
		sleep(1);
	}
	return 0;
}

#endif

#if 0
// thread.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
// 블럭 지정: ESC -> V
// 복사 방법: 범위 지정 후 -> y(yark)
// 붙여 넣기: ESC -> p(paste)
void* thread_func(void* arg) {
	const char* p = (const char*)arg;
	int i;
	for(i = 0; i < 5; i++) {
		printf("%s\n", p);
		sleep(1);
	}
	return NULL;
}

// 스레드 코드를 빌드할 경우, -lpthread 옵션을 사용해야 합니다
int main()
{
	pthread_t tid;
	
	// 스레드를 생성하는 방법
	pthread_create(&tid, 0, thread_func, "\tWorker Thread");	// fork

	// 스레드의 종료를 대기하는 방법
	pthread_join(tid, NULL);									// wait
	return 0;
}


#endif

// pthread_join의 사용 방법
#include <stdio.h>
#include <stdlib.h>	// for malloc
#include <unistd.h>
#include <pthread.h>
void* create_array(void* arg) {
	const int* pLen = (const int*)arg;
	return calloc(*pLen, sizeof(int));
}

int main() {
	int len = 5;
	pthread_t tid;
	pthread_create(&tid, 0, create_array, &len);

	int* pArr;
	pthread_join(tid, (void**)&pArr);	
	
	int i;
	for(i = 0; i < len; i++)
		printf("%d ", pArr[i]);
	printf("\n");

	free(pArr);
	return 0;
}


