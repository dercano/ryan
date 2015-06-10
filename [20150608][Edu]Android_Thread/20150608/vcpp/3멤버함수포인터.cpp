
// 2.cpp�� ��� ������ ������ ������ :D

#include <stdio.h>

// ���� �Լ�
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
	// ���� �Լ��� ������
	void(*fp1)(int) = func;	// __cdecl ����� �Լ� ������
	fp1(10);

	// Ŭ���� �Լ�(���� ��� �Լ�, Ŭ���� �޼���)
	void(*fp2)(int) = &Clazz::static_function;	// Clazz.static_function;
	fp2(10);
	// ���� ��� �Լ��� �Ϲ� �Լ� �����Ϳ� ����� �� �ִ�.

	// �ν��Ͻ� �Լ�(�Ϲ� ��� �Լ�, �ν��Ͻ� �޼���)
	void(Clazz::*fp3)(int) = &Clazz::function;	// __thiscall ����� �Լ� ������
	// fp3(10);	// Error, ��ü�� ������ ����
	Clazz obj;

	// obj.fp3(10);	// ERROR
	// fp3(&obj, 10);	// ERROR
	(obj.*fp3)(10);

	Clazz* pObj = new Clazz;	// Clazz obj = new Clazz();
	// (pObj.*fp3)(10);
	(pObj->*fp3)(10);
}

