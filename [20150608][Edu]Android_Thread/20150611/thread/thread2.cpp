
#if 0
// thread2.cpp
#include <unistd.h>
#include <stdio.h>

#include <utils/Thread.h>
using namespace android;

class MyThread : public Thread {
	bool flag;
public:
	MyThread() : flag(false) {}
	void stop() { flag = true; }

	bool threadLoop() {
		if(flag) return false;
		
		printf("MyThread...\n");
		sleep(1);
		return true;	// loop mode
	}
};

int main() {
	sp<MyThread> thread = new MyThread();
	thread->run();					
	getchar();

	thread->stop();
	getchar();

	return 0;
}

#endif



#include <unistd.h>
#include <stdio.h>

#include <utils/Thread.h>
using namespace android;

class MyThread : public Thread 
{
public:
	bool threadLoop() {
		printf("MyThread...\n");
		sleep(1);
		return true;	// loop mode
	}
};

int main() {
	sp<MyThread> thread = new MyThread();
	thread->run();					
	getchar();

	thread->requestExit();
	getchar();

	return 0;
}




















