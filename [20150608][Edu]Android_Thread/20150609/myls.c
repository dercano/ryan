
#if 0
// myls.c
#include <stdio.h>
#include <unistd.h>

// # ls
// hello world.java c.c
// # 
int main()
{
	puts("# ls");	// printf
	execlp("ls", "ls", (char*)0);
	puts("# ");
}

#endif



#if 0
// 아래의 코드는 동기적으로 실행되지 않습니다.
// myls.c
#include <stdio.h>
#include <unistd.h>

// # ls
// hello world.java c.c
// # 
int main()
{
	puts("# ls");

	if(fork() == 0)	{	// in child process
		execlp("ls", "ls", (char*)0);
	}

	sleep(1);
	puts("# ");
}
#endif

// 이제 동기적으로 변경해 봅니다.
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	puts("# ls");
	if(fork() == 0)	{	// in child process
		execlp("ls", "ls", (char*)0);
	}

	wait(0);	// sleep(1);
	puts("# ");
}





















