
// 1. extends Thread
// 2. override threadLoop in Thread
// 3. call run
#include <unistd.h>
#include <stdio.h>

#include <utils/Thread.h>
using namespace android;

class MyThread : public Thread
{
public:
	bool threadLoop() {
		for(int i = 0; i < 10; i++) {
			printf("MyThread...\n");
			sleep(1);
		}
		return false;
	}
};

int main()
{
	MyThread thread;
	thread.run();
	getchar();
	return 0;
}

