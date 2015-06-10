
#if 0
#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("hello, world");
	_exit(0);	// exit(0);	// return 0;
}
#endif


#if 0
// 리눅스/유닉스의 전통적인 에러 처리 방법
#include <stdio.h>


int main() {
	// 전통적인 C 라이브러리들은 에러 코드를 출력하기 위해 리턴 값을 사용합니다.
	FILE* fp = fopen("a.txt", "r");
	if(fp == NULL) {
		fprintf(stderr, "fopen error\n");
		return -1;
	}

	char buff[1024];	// application buffer
	fgets(buff, sizeof(buff), fp);
	printf("%s\n", buff);

	fclose(fp);
	return 0;
}

// 단점: 오류가 발생한 원인을 모른다
#endif


#if 0
#include <stdio.h>
// errno 변수를 사용하기 위해 아래의 헤더 파일을 제공합니다.
#include <errno.h>	// extern int errno;

// 헤더 파일의 정의 보기: CTRL + WF(Window + FILE)
// 헤더 파일의 창을 종료: CTRL + WC(Window + Close)

int main() {
	// 오류가 발생할 경우, 오류 코드를 남깁니다(errno).
	FILE* fp = fopen("a.txt", "r");
	if(fp == NULL) {
		fprintf(stderr, "fopen error: %d\n", errno);
		return -1;
	}

	char buff[1024];	// application buffer
	fgets(buff, sizeof(buff), fp);
	printf("%s\n", buff);

	fclose(fp);
	return 0;
}


#endif

#if 0
#include <stdio.h>
#include <string.h>
#include <errno.h>	// extern int errno;

int main() {
	FILE* fp = fopen("a.txt", "r");
	if(fp == NULL) {
		fprintf(stderr, "fopen error: %s\n", strerror(errno));
		return -1;
	}

	char buff[1024];	// application buffer
	fgets(buff, sizeof(buff), fp);
	printf("%s\n", buff);

	fclose(fp);
	return 0;
}
// 문제: 에러 문자열을 출력하기 너무 번거롭다.
#endif


#include <stdio.h>
#include <string.h>
#include <errno.h>	// extern int errno;

// perror 함수는 오류 메시지를 출력합니다.
int main() {
	FILE* fp = fopen("a.txt", "r");
	if(fp == NULL) {
		perror("fopen");	//fprintf(stderr, "fopen error: %s\n", strerror(errno));
		return -1;
	}

	char buff[1024];
	fgets(buff, sizeof(buff), fp);
	printf("%s\n", buff);

	fclose(fp);
	return 0;
}
// 문제: 에러 문자열을 출력하기 너무 번거롭다.
