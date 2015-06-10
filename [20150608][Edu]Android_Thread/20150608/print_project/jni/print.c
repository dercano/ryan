
// print.c
#include <stdio.h>

int main(int argc, char* argv[])
{
	if(argc != 2) {
		printf("usage: %s <STRING>\n", argv[0]);
		return -1;
	}

	printf("%s\n", argv[1]);
	return 0;
}
