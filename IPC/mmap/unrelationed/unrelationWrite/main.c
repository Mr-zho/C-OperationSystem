#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/wait.h>


int main()
{
    /* 获取文件大小 */   
    char * name = "./tongxin.txt"; 
    int fd = open(name, O_RDWR);
    if (fd == -1)
    {
        perror("open error");
        exit(-1);
    }

    /* 获取文件大小 */
    off_t len = lseek(fd, 0, SEEK_END);
    printf("len:%ld\n", len);

    void * addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmao error");
        exit(-1);
    }
    /* 关闭文件 */
    close(fd);

    /* 创建进程 */
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        exit(-1);
    }
    else if (pid == 0)
    {
        /* 子进程 */
        /* 读数据 */
        usleep(1000);
        printf("buffer:%s\n", (char *)addr);
    }
    else
    {
        /* 父进程 */
        /* 写数据 */
        char * str = "hello world";
        strncpy((char *)addr, str, strlen(str) + 1);
            
        /* 回收子进程资源 */
        wait(NULL);
    }
    printf("addr: %p\n", addr);

    /* 解除映射 */
    munmap(addr, len);
}
