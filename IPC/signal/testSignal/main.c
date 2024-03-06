#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#define BUFFER_SIZE	32

int g_fd = 0;

/* 钩子要求: 函数命名一定要有Handler,  */
void sigHandler(int num)
{
	printf("hello 257 257 257, num:%d\n", num);
	close(g_fd);
	exit(0);
}
int main()
{

	signal(SIGINT, sigHandler);
	
	const char * name = "./test.txt";
	g_fd = open(name, O_RDWR | O_CREAT, 0644);
	if (g_fd == -1)
	{
		perror("open error");
		exit(-1);
	}

	char buffer[BUFFER_SIZE] = { 0 };
	strcpy(buffer, "hello world\n");

	int count = 10;
	int writeBytes = 0;
	while (count--)
	{

		writeBytes = write(g_fd, buffer, strlen(buffer) + 1);
		printf("write Bytes:%d\n", writeBytes);
		if (writeBytes < 0)
		{
			perror("write error");
			exit(-1);
		}
		sleep(1);
	}

	/* 关闭文件描述符 */
	close(g_fd);
	return 0;
}
