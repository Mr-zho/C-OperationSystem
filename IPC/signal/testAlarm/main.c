#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main()
{
	/* 设置定时器 */
	alarm(5);

	int count = 10;
	while (count--)
	{
		printf("hello world\n");
		sleep(1);
	}
	return 0;
}
