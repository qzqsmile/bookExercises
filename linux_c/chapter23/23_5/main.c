#include<stdio.h>
#include"para_callback.h"

static void say_hello(void *str)
{
	printf("Hello %s\n", (const char *)str);
}

static void count_numbers(void *num)
{
	int i;
	for (i = 1; i <= (int)num; i++)
		printf("%d ",i);
	putchar('\n');
}

int main(void)
{
	repeat_three_times(say_hello, "Guys");
	repeat_three_times(count_numbers, (void *)4);
	return 0;
}
