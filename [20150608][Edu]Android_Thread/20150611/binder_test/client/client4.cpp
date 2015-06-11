
#include "Android.h"

class ProcessState {
	int mDriverFD;
	static ProcessState* pInstance;	// 전역 변수 선언

	ProcessState() : mDriverFD(open_driver()) {}
	ProcessState(const ProcessState&);
	void operator=(const ProcessState&);

	int open_driver() { return binder_open(128*1024); }
public:
	static ProcessState* self() {	// getInstance() {
		if(pInstance == 0)
			pInstance = new ProcessState;
		return pInstance;
	}
	int get_driver() const { return mDriverFD; }
};
ProcessState* ProcessState::pInstance = 0;

// binder_call 함수의 사용이 너무 복잡합니다. 이를 간단하게 사용할 수 있도록
// 클래스를 도입합니다
class IPCThreadState
{
	ProcessState* mProcess;
public:
	IPCThreadState() : mProcess(ProcessState::self()) {}

	// binder_call의 래퍼를 제공합니다. 안드로이드에서는 transact 함수를 사용합니다.
	int transact(int handle, int code, int* msg, int* reply) {
		return binder_call(mProcess->get_driver(), msg, reply, handle, code);
	}
};

int main(int argc, const char *argv[]) {
	ProcessState* proc(ProcessState::self());
	IPCThreadState* ipc(new IPCThreadState);

	int msg, reply;
//	int handle = binder_call(proc->get_driver(), (int*)"LedService", &reply,
//			BINDER_SERVICE_MANAGER,	SVC_MGR_CHECK_SERVICE);
	int handle = ipc->transact(BINDER_SERVICE_MANAGER, SVC_MGR_CHECK_SERVICE,
			(int*)"LedService", &reply);

	while (1) {
//		getchar(); binder_call(proc->get_driver(), &msg, &reply, handle, 1);
		getchar(); ipc->transact(handle, 1, &msg, &reply);
//		getchar(); binder_call(proc->get_driver(), &msg, &reply, handle, 2);
		getchar(); ipc->transact(handle, 2, &msg, &reply);
	}
	return 0;
}
