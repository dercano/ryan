
// IPCThreadState.cpp

// IPCThreadState 클래스는 프로세스 싱글턴을 사용하는 것이 아닌
// 쓰레드 싱글턴을 사용합니다. 쓰레드 싱글턴은 하나의 쓰레드에 오직 유일한
// 객체를 만드는 기술입니다. 이 기술을 사용하려면 TLS(Thread Local Storage)를
// 사용해야 합니다.
#include <stdio.h>
#include <pthread.h>

bool gHaveTLS = false;	// TLS 생성 유무를 위한 플래그 입니다.
pthread_key_t gTLS = 0;

class IPCThreadState
{
	// 1. 생성자를 private 영역에 정의해야 합니다.
	IPCThreadState() {
		pthread_setspecific(gTLS, this);
		printf("IPCThradState()\n");
	}

public:
	static void threadDestructor(void* p) {}
	void joinThreadPool() {}

	static IPCThreadState* self() {
		if(gHaveTLS) {
restart:
			const pthread_key_t k = gTLS;
			IPCThreadState* state = (IPCThreadState*)pthread_getspecific(k);
			if(state)
				return state;
			return new IPCThreadState();
		}

		if(!gHaveTLS) {	// TLS를 사용하지 않았다면 초기화합니다.
			if(pthread_key_create(&gTLS, threadDestructor) != 0)
				return NULL;
			gHaveTLS = true;
		}
		goto restart;
	}
};

void* thread_func(void* arg) {
	IPCThreadState::self();
	IPCThreadState::self();
	IPCThreadState::self();
	IPCThreadState::self();
	IPCThreadState::self();
	IPCThreadState::self();
	return 0;
}

int main()
{
	IPCThreadState::self();
	IPCThreadState::self();
	IPCThreadState::self();
	IPCThreadState::self();
	IPCThreadState::self();

	getchar();
	
	pthread_t t;
	pthread_create(&t, 0, thread_func, 0);
	pthread_join(t, 0);

	return 0;
}









