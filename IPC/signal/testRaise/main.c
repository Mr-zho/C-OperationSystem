#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	int count = 10;
	while (count--)
	{
		if (count == 5)
		{
			raise(SIGKILL);
		}
		printf("hello world\n");
		sleep(1);
	}
	return 0;
}
