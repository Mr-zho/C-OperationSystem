#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <error.h>

/* 
    为什么要有进程间通信? 
        因为进程具有独立的地址空间, 所以必须要有通信机制. IPC
*/

#define PIPE_SIZE   2
#define BUFFER_SIZE 32

int main()
{
    int pipefd[PIPE_SIZE] = {0};

    /* 创建管道 */
    int ret = pipe(pipefd);
    if (ret == -1)
    {
        perror("pipe error");
        exit(-1);
    }

    /* 创建进程 */
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        exit(-1);
    }
    else if (pid == 0)
    {
        sleep(2);
        /* 子进程读 */
        /* pipefd[0]: 读 */
        /* 将写端关闭 */
        close(pipefd[1]);

        /* 获取文件描述符当前属性 */
        int flag = fcntl(pipefd[0], F_GETFL);

        /* 设置成非阻塞 */
        flag |= O_NONBLOCK;
        fcntl(pipefd[0], F_SETFL, flag);

        char buffer[BUFFER_SIZE] = {0};
        int readBytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (readBytes < 0)
        {
            if (errno == EAGAIN)
            {
                printf("heiheihei\n");
            }
            else
            {
                perror("read error");
            }
        }
        else if (readBytes == 0)
        {
            printf("readBytes == 0\n");
        }
        else
        {
            printf("child --- readBytes:%d,\tbuffer:%s\n", readBytes, buffer);
        }

        /* 关闭读端 */
        close(pipefd[0]);
    }
    else
    {
        /* 父进程写 */
        /* pipefd[1]: 写 */
        /* 将读端关闭 */
        close(pipefd[0]);

        char * str = "hello world";
        write(pipefd[1], str, strlen(str) + 1);

#if 0
        char buf[BUFFER_SIZE] = { 0 };
        int readBytes = read(pipefd[0], buf, sizeof(buf) - 1);
        if (readBytes < 0)
        {

        }
        else if (readBytes == 0)
        {

        }
        else
        {
            printf("parent --- readBytes:%d,\tbuffer:%s\n", readBytes, buf);
        }
#endif
        

        /* 回收子进程资源 */
        wait(NULL);
        
        /* 关闭写端 */
        close(pipefd[1]);
    }

    return 0;
}