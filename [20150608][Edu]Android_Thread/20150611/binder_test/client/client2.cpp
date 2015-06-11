
#include "Android.h"

class ProcessState {
	int mDriverFD;
	int open_driver() { return binder_open(128*1024); }
public:
	ProcessState() : mDriverFD(open_driver()) {}
	int get_driver() const { return mDriverFD; }
};

int main(int argc, const char *argv[]) {
//	ProcessState proc;
	// 대용량의 자료구조를 스택에 생성하는 것은 좋은 방법이 아닙니다.
	// 이제 힙에 생성합니다
//	ProcessState* proc = new ProcessState();
	ProcessState* proc(new ProcessState());

	int msg, reply;
	int handle = binder_call(proc->get_driver(), (int*)"LedService", &reply,
			BINDER_SERVICE_MANAGER,	SVC_MGR_CHECK_SERVICE);

	while (1) {
		getchar(); binder_call(proc->get_driver(), &msg, &reply, handle, 1);
		getchar(); binder_call(proc->get_driver(), &msg, &reply, handle, 2);
	}
	return 0;
}
