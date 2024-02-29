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
    int fd1 = open(name, O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd1 == -1)
    {
        perror("open error");
        return -1;
    }
    printf("fd1:%d\n", fd1);

    char buffer[BUFFER_SIZE] = { 0 };
    int readBytes = 0;
    while (1)
    {
        readBytes = read(fd1, buffer, BUFFER_SIZE - 1);
        if (readBytes < 0)
        {
            perror("read error");
            return -1;
        }
        if (readBytes == 0)
        {
            /* 上一次就已经全部读取完毕 */
            break;
        }
        else
        {
            if (readBytes < BUFFER_SIZE - 1)
            {
                buffer[readBytes] = '\0';
            }
            printf("readBytes:%d,\tbuffer:%s\n", readBytes, buffer);
        }
    }
    /* 回收资源 */
    close(fd1);

    printf("hello world\n");
    return 0;
}