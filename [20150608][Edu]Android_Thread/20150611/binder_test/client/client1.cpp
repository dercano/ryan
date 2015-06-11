
// client1.cpp
#include "Android.h"

// 바인더 정보를 관리하는 클래스를 도입합니다.
class ProcessState {
	int mDriverFD;
	
	// 리소스 할당 정책은 한 곳으로 모아야 합니다.
	int open_driver() { return binder_open(128*1024); }
public:
//	ProcessState() : mDriverFD(binder_open(128*1024)) {}
	ProcessState() : mDriverFD(open_driver()) {}
	int get_driver() const { return mDriverFD; }
};

int main(int argc, const char *argv[]) {
//	int fd = binder_open(128*1024);
//	fd = 0;
//	ProcessState proc(fd);
	ProcessState proc;

	int msg, reply;
	int handle = binder_call(proc.get_driver(), (int*)"LedService", &reply,
			BINDER_SERVICE_MANAGER,	SVC_MGR_CHECK_SERVICE);

	while (1) {
//		getchar(); binder_call(fd, &msg, &reply, handle, 1);
		getchar(); binder_call(proc.get_driver(), &msg, &reply, handle, 1);
//		getchar(); binder_call(fd, &msg, &reply, handle, 2);
		getchar(); binder_call(proc.get_driver(), &msg, &reply, handle, 2);
	}

	return 0;
}
