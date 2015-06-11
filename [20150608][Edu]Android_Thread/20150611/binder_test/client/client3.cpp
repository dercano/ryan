
#include "Android.h"

// 이제 아래의 클래스를 싱글톤 형태로 구현합니다
class ProcessState {
	int mDriverFD;

	// 1. 생성자를 private 영역에 정의해야 합니다.
	ProcessState() : mDriverFD(open_driver()) {}
	int open_driver() { return binder_open(128*1024); }

	// 3. 복사 생성자와 대입 연산자 함수를 private 영역에 선언만 해야합니다.
	ProcessState(const ProcessState&);
	void operator=(const ProcessState&);

	static ProcessState* pInstance;	// 전역 변수 선언
public:
	// 2. 유일한 객체가 반환될 수 있도록 정적 인터페이스를 제공해야 합니다.
	static ProcessState* self() {	// getInstance() {
		if(pInstance == 0)
			pInstance = new ProcessState;
		return pInstance;
	}
	int get_driver() const { return mDriverFD; }
};
ProcessState* ProcessState::pInstance = 0;

int main(int argc, const char *argv[]) {
//	ProcessState* proc(new ProcessState());
//	ProcessState* proc(ProcessState::getInstance());
	ProcessState* proc(ProcessState::self());

	int msg, reply;
	int handle = binder_call(proc->get_driver(), (int*)"LedService", &reply,
			BINDER_SERVICE_MANAGER,	SVC_MGR_CHECK_SERVICE);

	while (1) {
		getchar(); binder_call(proc->get_driver(), &msg, &reply, handle, 1);
		getchar(); binder_call(proc->get_driver(), &msg, &reply, handle, 2);
	}
	return 0;
}
