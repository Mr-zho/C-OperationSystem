#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/* 全局变量 */
int g_data = 666;

int main()
{
    /* 局部的变量 */
    int val = 100;

    
#if 1
    /* 创建进程 */
    pid_t pid = fork(); 
    if (pid < 0)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        sleep(1);

        int fd = open("./test.txt", O_RDONLY);
        if (fd == -1)
        {
            perror("open error");
            return -1;
        }
        /* 子进程 */
        printf("child: val:%d\n", val);
        printf("child: g_data:%d\n", g_data);

        int data = 0;
        int readBytes = read(fd, (void *)&data, sizeof(int));
        if (readBytes < 0)
        {

        }
        else if (readBytes == 0)
        {

        }
        else
        {
            printf("child ================  data:%d\n", data);
        }
        if (g_data == 1000)
        {
            // exeute()
        }
    }
    else
    {
        /* 父进程 */
        int fd = open("./test.txt", O_WRONLY | O_CREAT, 0644);
        if (fd == -1)
        {
            perror("open error");
            return -1;
        }
        printf("parent: val:%d\n", val);
        printf("parent: g_data:%d\n", g_data);
        val += 666;
        printf("parent: val:%d\n", val);
        g_data += 222;
        printf("parent: g_data:%d\n", g_data);

        int writeBytes = write(fd, (void *)&g_data, sizeof(int));
        if (writeBytes == -1)
        {
            perror("write error");
            return -1;
        }
        printf("writeBytes:%d\n", writeBytes);

        close(fd);
    }
#else

    /* 父进程 */
    int fd = open("./test.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open error");
        return -1;
    }

    /* 创建进程 */
    pid_t pid = fork(); 

    if (pid < 0)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        sleep(1);
        
        /* 子进程 */
        printf("child: val:%d\n", val);
        printf("child: g_data:%d\n", g_data);

        /* 文件指针复原到文件开头 */
        lseek(fd, 0, SEEK_SET);

        int data = 0;
        int readBytes = read(fd, (void *)&data, sizeof(int));
        if (readBytes < 0)
        {
            perror("read error");
            return -1;
        }
        else if (readBytes == 0)
        {
            printf("readBytes == 0");
        }
        else
        {
            printf("child ================  data:%d\n", data);
        }
        if (g_data == 1000)
        {
            // exeute()
        }
    }
    else
    {
        printf("parent: val:%d\n", val);
        printf("parent: g_data:%d\n", g_data);
        val += 666;
        printf("parent: val:%d\n", val);
        g_data += 222;
        printf("parent: g_data:%d\n", g_data);

        int writeBytes = write(fd, (void *)&g_data, sizeof(int));
        if (writeBytes == -1)
        {
            perror("write error");
            return -1;
        }
        printf("writeBytes:%d\n", writeBytes);

        
    }
    printf("hello world...........\n");
    sleep(10);
    close(fd);

#endif

    sleep(3);

    return 0;
}