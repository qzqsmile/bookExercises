#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	
	printf("fd is = %d\n", fd);
	printf("fd 0: %s\n", ttyname(0));
	printf("fd 1: %s\n", ttyname(1));
	printf("fd 2: %s\n", ttyname(2));

	return 0;
}
