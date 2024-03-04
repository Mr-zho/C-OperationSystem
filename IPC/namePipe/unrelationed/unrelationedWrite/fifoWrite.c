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


#define BUFFER_SIZE 32

int main()
{
    const char * fileName = "../fifoInfo";

    int ret = access(fileName, F_OK);
    if (ret == -1)
    {
        /* 管道文件不存在 */
        /* 创建命名管道 */
        int ret = mkfifo(fileName, 0644);
        if (ret == -1)
        {
            if (errno != EEXIST)
            {
                perror("mkfifo error");
                exit(-1);
            }
        }
    }

 
    /* 打开管道文件 */
    /* 必选项: 只读 / 只写 / 可读可写
    可选项: { 追加 ｜ 创建 ｜ 清空 }
    */
    int fd = open(fileName, O_RDWR);
    if (fd == -1)
    {
        perror("open error");
    }

    char buf[BUFFER_SIZE] = { 0 };
    int cnt = 3;

    int writeBytes = 0;
    while (1)
    {
        strcpy(buf, "hello world");

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
        /* 清除脏数据 */
        memset(buf, 0, sizeof(buf));

        sleep(3);
    }

    /* 关闭文件描述符, 回收资源. */
    close(fd);


    return 0;
}
