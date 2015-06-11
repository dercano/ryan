
#include "Android.h"

class ProcessState {
	int mDriverFD;
	static ProcessState* pInstance;

	ProcessState() : mDriverFD(open_driver()) {}
	ProcessState(const ProcessState&);
	void operator=(const ProcessState&);

	int open_driver() { return binder_open(128*1024); }
public:
	static ProcessState* self() {
		if(pInstance == 0)
			pInstance = new ProcessState;
		return pInstance;
	}
	int get_driver() const { return mDriverFD; }
};
ProcessState* ProcessState::pInstance = 0;

// 싱글 쓰레드에서 하나 이상의 객체를 생성하는 것은 좋지 못하다.
// 그래서 싱글톤을 도입합니다.
class IPCThreadState
{
	ProcessState* mProcess;
	static IPCThreadState* pInstance;

	IPCThreadState() : mProcess(ProcessState::self()) {}
	IPCThreadState(const IPCThreadState&);
	void operator=(const IPCThreadState&);

public:
	static IPCThreadState* self() {
		if(pInstance == 0)
			pInstance = new IPCThreadState;
		return pInstance;
	}

	int transact(int handle, int code, int* msg, int* reply) {
		return binder_call(mProcess->get_driver(), msg, reply, handle, code);
	}
};
IPCThreadState* IPCThreadState::pInstance = 0;

int main(int argc, const char *argv[])
{
	ProcessState* proc(ProcessState::self());
//	IPCThreadState* ipc(new IPCThreadState);
	IPCThreadState* ipc(IPCThreadState::self());

	int msg, reply;
	int handle = ipc->transact(BINDER_SERVICE_MANAGER, SVC_MGR_CHECK_SERVICE,
			(int*)"LedService", &reply);

	while (1) {
		getchar(); ipc->transact(handle, 1, &msg, &reply);
		getchar(); ipc->transact(handle, 2, &msg, &reply);
	}
	return 0;
}
