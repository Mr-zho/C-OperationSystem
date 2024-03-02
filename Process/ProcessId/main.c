#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* 什么叫程序 什么叫代码 什么叫进程 */

/* 什么情况下会导致CPU飙升? 死循环. */
int main()
{

    pid_t pid = getpid();
    printf("pid is = %d\n", pid);

    pid_t ppid = getppid();
    printf("ppid is %d\n", ppid);
    
    int count = 30;
    while (count--)
    {
        sleep(1);
    }

    return 0;
}