
// Singleton

// cursor.cpp
#include <stdio.h>

class Mutex {
public:
	void lock() { printf("Mutex::lock()\n"); }
	void unlock() { printf("Mutex::unlock()\n"); }
};

class Autolock {
	Mutex& o;
public:
	Autolock(Mutex& m) : o(m) { o.lock(); }
	Autolock(Mutex* m) : o(*m) { o.lock(); }
	~Autolock() { o.unlock(); }
};

class Cursor {
	// 1. 사용자가 객체를 임의로 생성할 수 없도록 생성자를 private 영역에
	// 정의해야 합니다.
	Cursor() {}

	// 3. 복사와 대입을 금지하기 위하여 복사 생성자와 대입 연산자 함수를
	// private 영역에 선언합니다. 
	Cursor(const Cursor&);
	void operator=(const Cursor&); 

	static Mutex mutex;
	static Cursor* pInstance;
public:
	// 2. 유일한 객체를 반환하기 위한 정적 인터페이스를 제공합니다.
	static Cursor& getInstance() {
		Autolock l(mutex);	// 리소스는 객체가 생성될 때 획득하자(RAII)
//		mutex.lock();
		//-------------------------
		if(pInstance == 0)
			pInstance = new Cursor;
		//-------------------------
//		mutex.unlock();
		return *pInstance;
	}
};
Cursor* Cursor::pInstance = 0;
Mutex Cursor::mutex;

int main() {
	Cursor& c1 = Cursor::getInstance();
	Cursor& c2 = Cursor::getInstance();

	printf("c1 = %p\n", &c1);
	printf("c2 = %p\n", &c2);
}
