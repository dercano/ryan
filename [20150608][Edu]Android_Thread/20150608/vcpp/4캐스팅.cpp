
#if 0
// 캐스팅
// 잠시 현재 파일의 확장자를 .cpp로 변경해보세여
#include <stdlib.h>

int main()
{
	// 근본적으로 포인터 사이의 호환성이 없기 때문
	// char* p = (char*)malloc(sizeof(char));

	// 명시적 변환을 사용하면 안되는 이유: 컴파일러의 타입 체크
	// 기능이 꺼지게 됩니다.

	// static_cast: 이성적인 형 변환을 할 때 사용합니다.
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

	// reinterpret_cast: 비 이성적인 형 변환을 할 때 사용
	// C 언어의 대부분의 형 변환을 지원
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

	// const_cast: 상수 객체를 비상수 타입으로 변경하기 위해 사용
	int* p = const_cast<int*>(&n);
	printf("%d\n", n);
}