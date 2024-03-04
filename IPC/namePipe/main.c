#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>


#define BUFFER_SIZE 5
int main()
{
    /* 创建命名管道 */
    const char * fileName = "./fifoInfo";
    int ret = mkfifo(fileName, 0644);
    if (ret == -1)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo error");
            exit(-1);
        }
    }

    

    /* 创建进程 */
    pid_t pid = fork();
    if (pid < 0)
    {

    }
    else if (pid == 0)
    {
        printf("child process\n");
        /* 打开管道文件 */
        /* 必选项: 只读 / 只写 / 可读可写
        可选项: { 追加 ｜ 创建 ｜ 清空 }
        */
        int fd = open(fileName, O_RDWR);
        if (fd == -1)
        {
            perror("open error");
        }

        /* 设置非阻塞 */
        int flag = fcntl(fd, F_GETFL);
        flag |= O_NONBLOCK;
        fcntl(fd, F_SETFL, flag);

        char buffer[BUFFER_SIZE] = { 0 };
        int readBytes = 0;
        while (1)
        {
            readBytes = read(fd, buffer, BUFFER_SIZE - 1);
            if (readBytes < 0)
            {
                if (errno == EAGAIN)
                {
                    break;
                }
                else
                {
                    perror("read error");
                    close(fd);
                    exit(-1);
                } 
            }
            else if (readBytes == 0)
            {
                printf("readBytes == 0");
                break;
            }
            else
            {
                printf("readBytes = %d\t, buffer:%s\n", readBytes, buffer);
            }
            sleep(2);
        }
        /* 关闭文件描述符 */
        close(fd);
    }
    else
    {
        printf("parent process\n");
        
        /* 打开管道文件 */
        /* 必选项: 只读 / 只写 / 可读可写
        可选项: { 追加 ｜ 创建 ｜ 清空 }
        */
        int fd = open(fileName, O_RDWR);
        if (fd == -1)
        {
            perror("open error");
        }

        char * buf = "hello world";
        int cnt = 3;

        int writeBytes = 0;
        while (cnt--)
        {
            writeBytes = write(fd, buf, strlen(buf) + 1);
            if (writeBytes < 0)
            {
                perror("write error");
            }
            else if (writeBytes == 0)
            {
                printf("buffer overflow...\n");
            }
            else
            {
                printf("writeBytes = %d\n", writeBytes);
            }
            sleep(1);
        }

        /* 关闭文件描述符, 回收资源. */
        close(fd);

        /* 回收子进程资源 */
        wait(NULL);
    }



    return 0;
}