#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 5

int main()
{
    const char * name = "./test.txt";
    int fd1 = open(name, O_RDWR);
    if (fd1 == -1)
    {
        perror("open error");
        return -1;
    }
    printf("fd1:%d\n", fd1);

    char buffer[BUFFER_SIZE] = { 0 };
    int readBytes = read(fd1, buffer, sizeof(buffer) - 1);
    printf("readBytes:%d,\tbuffer:%s\n", readBytes, buffer);

    int offset = lseek(fd1, -1, SEEK_CUR);
    printf("offset:%d\n", offset);

    char ch = '0';
    read(fd1, &ch, 1);
    printf("ch:%c\n", ch);

    /* 计算文件大小 */
    offset = lseek(fd1, 0, SEEK_END);
    printf("offset:%d\n", offset);





    /* 回收资源 */
    close(fd1);

    printf("hello world\n");
    return 0;
}