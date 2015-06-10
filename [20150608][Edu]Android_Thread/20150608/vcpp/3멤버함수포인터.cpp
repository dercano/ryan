
// 2.cpp의 모든 내용을 복사해 오세여 :D

#include <stdio.h>

// 전역 함수
void func(int a) { printf("called func(%d)\n", a); }

class Clazz	// small namespace
{
public:
	void function(int a) {
		printf("called Clazz::function(%d)\n", a);
	}

	static void static_function(int a) {
		printf("called Clazz::static_function(%d)\n", a);
	}
};
void main()
{
	// 전역 함수의 포인터
	void(*fp1)(int) = func;	// __cdecl 방식의 함수 포인터
	fp1(10);

	// 클래스 함수(정적 멤버 함수, 클래스 메서드)
	void(*fp2)(int) = &Clazz::static_function;	// Clazz.static_function;
	fp2(10);
	// 정적 멤버 함수는 일반 함수 포인터에 저장될 수 있다.

	// 인스턴스 함수(일반 멤버 함수, 인스턴스 메서드)
	void(Clazz::*fp3)(int) = &Clazz::function;	// __thiscall 방식의 함수 포인터
	// fp3(10);	// Error, 객체의 정보가 음슴
	Clazz obj;

	// obj.fp3(10);	// ERROR
	// fp3(&obj, 10);	// ERROR
	(obj.*fp3)(10);

	Clazz* pObj = new Clazz;	// Clazz obj = new Clazz();
	// (pObj.*fp3)(10);
	(pObj->*fp3)(10);
}

