
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
    const char * fileName = "../fifoInfo";

    int ret = access(fileName, F_OK);
    if (ret == -1)
    {
        printf("fifoInfo not exist.");
        exit(-1);
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

#if 1
    /* 设置非阻塞 */
    int flag = fcntl(fd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
#endif

    char buffer[BUFFER_SIZE] = { 0 };
    int readBytes = 0;
    while (1)
    {
        /* 清除脏数据 */
        memset(buffer, 0, sizeof(buffer));


        readBytes = read(fd, buffer, BUFFER_SIZE - 1);
        if (readBytes < 0)
        {
            if (errno == EAGAIN)
            {
                printf("EAGAIN\n");
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
        sleep(4);
    }
    /* 关闭文件描述符 */
    close(fd);
   



    return 0;
}