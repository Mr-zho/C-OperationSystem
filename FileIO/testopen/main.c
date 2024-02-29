#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    const char * name = "./test.txt";
    int fd1 = open(name, O_RDWR | O_CREAT, 0644);
    if (fd1 == -1)
    {
        perror("open error");
        return -1;
    }
    printf("fd1:%d\n", fd1);

    int fd2 = open(name, O_RDWR | O_CREAT, 0644);
    if (fd2 == -1)
    {
        perror("open error");
        return -1;
    }
    printf("fd2:%d\n", fd2);


    int fd3 = open(name, O_RDWR | O_CREAT, 0644);
    if (fd3 == -1)
    {
        perror("open error");
        return -1;
    }
    printf("fd3:%d\n", fd3);

    int fd4 = open(name, O_RDWR | O_CREAT, 0644);
    if (fd4 == -1)
    {
        perror("open error");
        return -1;
    }
    printf("fd4:%d\n", fd4);

    /* 关闭文件描述符 资源回收 */
    close(fd3);


    int fd5 = open(name, O_RDWR | O_CREAT, 0644);
    if (fd5 == -1)
    {
        perror("open error");
        return -1;
    }
    printf("fd5:%d\n", fd5);





    printf("hello world\n");
    return 0;
}