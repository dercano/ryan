
#if 0
// ĳ����
// ��� ���� ������ Ȯ���ڸ� .cpp�� �����غ�����
#include <stdlib.h>

int main()
{
	// �ٺ������� ������ ������ ȣȯ���� ���� ����
	// char* p = (char*)malloc(sizeof(char));

	// ����� ��ȯ�� ����ϸ� �ȵǴ� ����: �����Ϸ��� Ÿ�� üũ
	// ����� ������ �˴ϴ�.

	// static_cast: �̼����� �� ��ȯ�� �� �� ����մϴ�.
	char* p = static_cast<char*>(malloc(sizeof(char)));
}
#endif

#if 0
#include <stdio.h>

int main()
{
	int n = 1;
	// char* p = (char*)&n;	// ?
	// char* p = static_cast<char*>(&n);

	// reinterpret_cast: �� �̼����� �� ��ȯ�� �� �� ���
	// C ����� ��κ��� �� ��ȯ�� ����
	char* p = reinterpret_cast<char*>(&n);
}
#endif

#include <stdio.h>

int main()
{
	const int n = 20;
	// n = 0;
	// int* pInt = (int*)&n; *pInt = 0;
	// int* pInt = reinterpret_cast<int*>(&n);

	// const_cast: ��� ��ü�� ���� Ÿ������ �����ϱ� ���� ���
	int* p = const_cast<int*>(&n);
	printf("%d\n", n);
}