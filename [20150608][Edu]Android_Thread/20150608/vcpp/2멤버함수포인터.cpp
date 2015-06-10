
// 멤버 함수 포인터
#include <stdio.h>

// 전역 함수
void func(int a) { printf("called func(%d)\n", a); }

class Clazz
{
public:
	int val;
	static int static_val;	// extern int static_val;

	void function(int a)	// void function(Clazz* const this, int a);
	{
		val = 0;			// this->val = 0;
		static_val = 0;		// OK

		printf("called Clazz::function(%d)\n", a);
	}
	
	static void static_function(int a)	// void static_function(int a);
	{
		val = 0;			// this->val = 0; ERROR
		static_val = 0;		// OK

		printf("called Clazz::static_function(%d)\n", a);
	}
};
int Clazz::static_val = 0;

void main()
{
	// 전역 함수의 포인터
	void(*fp1)(int) = func;	fp1(10);

	// Clazz::static_val = 0;	// Clazz.static_val = 0;
	Clazz obj;
	obj.function(10);	// Clazz::function(&obj, 10);
}

