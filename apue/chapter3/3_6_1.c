#include"apue.h"

int main(void)
{
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
		printf("cannnot seek\n");
	else
		printf("seek Ok\n");
	exit(0);
}
