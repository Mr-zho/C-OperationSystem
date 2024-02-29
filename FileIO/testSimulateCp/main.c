#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 32

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        printf("missing destination file operand after 'test.txt'");
        return -1;
    }
    const char * srcName = argv[1];
    const char * dstName = argv[2];
    
    int srcfd = open(srcName, O_RDONLY);
    if (srcfd == -1)
    {
        perror("srcName open error");
        return -1;
    }

    int dstfd = open(dstName, O_WRONLY | O_CREAT, 0644);
    if (dstfd == -1)
    {
        perror("dstName open error");
        return -1;
    }

    char buffer[BUFFER_SIZE] = { 0 };
    int readBytes = 0;
    while (1)
    {
        readBytes = read(srcfd, buffer, BUFFER_SIZE - 1);
        if (readBytes < 0)
        {
            perror("read error");
            break;
        }
        else if (readBytes == 0)
        {
            break;
        }
        else if (readBytes > 0)
        {
            write(dstfd, buffer, readBytes);
        }
    }

    /* 回收资源 */
    close(srcfd);
    close(dstfd);

    return 0;
}