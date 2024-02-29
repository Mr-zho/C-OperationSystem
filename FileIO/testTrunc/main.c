#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 32

int main()
{
    const char * name = "./test.txt";

    int ret = truncate(name, 30);
    printf("ret:%d\n", ret);
    #if 0
    int fd1 = open(name, O_RDWR | O_TRUNC);
    if (fd1 == -1)
    {
        perror("open error");
        return -1;
    }
    printf("fd1:%d\n", fd1);

    char buffer[BUFFER_SIZE] = { 0 };
    int readBytes = read(fd1, buffer, sizeof(buffer) - 1);

    printf("readBytes:%d,\tbuffer:%s\n", readBytes, buffer);
    /* 回收资源 */
    close(fd1);
    #endif

    printf("hello world\n");
    return 0;
}