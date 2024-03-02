#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


/* 
    多进程, 并发处理 
        1. (优) 干活快          (效率)
        2. (缺) 消耗资源         (资源)
        3. 压力测试(性能瓶颈)
*/

int main()
{
    pid_t pid = fork();         // vfrok same effect fork. vfork让父进程代码先执行。
    if (pid < 0)
    {
        perror("fork error");
        return -1;
    }
    else if (pid == 0)
    {
        usleep(1000); // 1000us = 1ms = 0.001s
        /* 子进程和父进程执行的顺序是随机的, 先打印谁, 由操作系统决定. */
        printf("child process = %d,\tparent process = %d\n", getpid(), getppid());
        int count = 3;
        while (count--)
        {
            sleep(1);
        }
        int status = 1;
        _exit(status);
    }
    else
    {
        printf("pid = %d\n", pid);
        /* 子进程和父进程执行的顺序是随机的, 先打印谁, 由操作系统决定. */
        printf("parent process = %d,\tparent process = %d\n", getpid(), getppid());
        
        /* 阻塞函数: 程序卡在这边, 在等条件满足。在等子进程退出。*/
        #if 0
        int status = 0;
        wait(&status);

        printf("status:%d\n",  WEXITSTATUS(status));
        #else
        int status = 0;
        waitpid(pid, &status, 0);
        printf("status:%d\n",  WEXITSTATUS(status));
        #endif
    }
    /* 子进程退出, 但是没有回收子进程的资源 */
    printf("hello world");

    return 0;
}