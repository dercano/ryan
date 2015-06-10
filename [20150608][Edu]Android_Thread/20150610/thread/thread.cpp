
// thread.cpp
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// run, virtual function.
//void *(*start_routine) (void *)
class Thread
{
	pthread_t tid;

//	static Thread* self;

protected:	// 자식에게는 심볼이 보이나 외부에서는 심볼이 보이지 않음
	// 정적 함수는 일반 함수 포인터에 저장 가능
	static void* _threadLoop(void* arg) {	// void* _threadLoop(void* arg);
		Thread* self = static_cast<Thread*>(arg);
		self->threadLoop();	// this->threadLoop();
		return NULL;
	}

public:
	void run() {	// void run(Thread* const this);
//		self = this;
		pthread_create(&tid, 0, _threadLoop, this);
	}	

	virtual void* threadLoop() {	// void* threadLoop(Thread* const this);
		return NULL;
	}
};
//Thread* Thread::self = 0;

class MyThread : public Thread 
{
public:
	void* threadLoop() {
		for(int i = 0; i < 5; i++) {
			printf("Thread\n");
			sleep(1);
		}
		return NULL;
	}
};

int main() {
//	Thread* t = new Thread();
	Thread* t = new MyThread();
	t->run();
	getchar();
}
