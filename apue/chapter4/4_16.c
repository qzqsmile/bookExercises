#include"apue.h"
#include<fcntl.h>

int main(void)
{
	if(open("tempfile", O_RDWR) < 0)
		perror("open error");
	if(unlink("tempfile") < 0)
		perror("unlink error!\n");
	sleep(15);
	printf("done\n");
	exit(0);
}
