
#if 0

// thread1.cpp
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
		return true;	// true: loop mode
	}
};

int main()
{
//	Thread* thread = new MyThread();	// MyThread thread;
	sp<Thread> thread = new MyThread();	// smart pointer(strong pointer)
	thread->run();						//thread.run();
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
		for(int i = 0; i <10; i++) {
			printf("MyThread...\n");
			sleep(1);
		}
		return false;	// false: once
	}
};

int main()
{
	//	Thread* thread = new MyThread();	// MyThread thread;
	sp<Thread> thread = new MyThread();	// smart pointer(strong pointer)
	thread->run();						//thread.run();
	getchar();
	return 0;
}




















