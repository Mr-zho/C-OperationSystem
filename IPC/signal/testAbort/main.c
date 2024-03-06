#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main()
{
	int count = 10;
	while (count--)
	{
		if (count == 5)
		{
			/* 给自己发送终止信号 */
			abort();
		}
		printf("hello world\n");
		sleep(1);
	}
	return 0;
}
