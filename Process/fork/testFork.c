#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* 
    多进程, 并发处理 
        1. (优) 干活快          (效率)
        2. (缺) 消耗资源         (资源)
        3. 压力测试(性能瓶颈)
*/

int main()
{
    #if 1
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
        while (1)
        {
            sleep(1);
        }
        // 5000.
    }
    else
    {
        printf("pid = %d\n", pid);
        /* 子进程和父进程执行的顺序是随机的, 先打印谁, 由操作系统决定. */
        printf("parent process = %d,\tparent process = %d\n", getpid(), getppid());
        while (1)
        {
            sleep(1);
        }
    }
    #elif 0
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        return -1;
    }
    else if (pid == 0)
    {
        printf("child process = %d,\tparent process = %d\n", getpid(), getppid());
        while (1)
        {
            sleep(1);
        }
    }
    else
    {
        printf("parent process = %d,\tparent process = %d\n", getpid(), getppid());
    }
    /* 这种情况是父进程挂掉了, 子进程没人来回收, 会交由系统来管理回收。 孤儿进程. */
    #else
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        return -1;
    }
    else if (pid == 0)
    {    
        printf("child process = %d,\tparent process = %d\n", getpid(), getppid());    
    }
    else
    {
        printf("parent process = %d,\tparent process = %d\n", getpid(), getppid());
        while (1)
        {
            sleep(1);
        }
    }
    /* 总结: 子进程挂掉, 父进程没有回收他的资源. 子进程就会成为僵尸进程。(危害: 资源依旧被占用, 没有释放.)*/
    #endif


    return 0;
}