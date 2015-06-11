
// thread3.cpp
#include <unistd.h>
#include <stdio.h>

#include <utils/Thread.h>
using namespace android;

class MyThread : public Thread 
{
public:
	MyThread() { printf("MyThread::MyThread()\n"); }
    status_t readyToRun() { printf("MyThread::readyToRun()\n"); return NO_ERROR; }
    void onFirstRef() { printf("MyThread::onFirstRef()\n"); }

	bool threadLoop() {
		printf("MyThread...\n");
		sleep(10);
		return false;	// once
	}
};

int main() {
	sp<MyThread> thread = new MyThread();
	thread->run();					

	thread->join();	// block
	printf("exit MyThread\n");
	getchar();

	return 0;
}




















