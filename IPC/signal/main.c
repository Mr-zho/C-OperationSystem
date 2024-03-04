#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int myDiv(int num1, int num2)
{   
    return num1 / num2;
}

#define PIPE_SIZE 2
#define BUFFER_SIZE 10

int main()
{
    #if 0
    int ret = myDiv(10, 0);
    printf("ret:%d\n", ret);
    #endif

    #if 0
    char * str = NULL;
    strcpy(str, "hello world");
    #endif

    /* 除了 {-1, 0, 1} 以外的所有都叫魔数. */

    pid_t pid = fork();
    if (pid < 0)
    {

    }
    else if (pid == 0)
    {
        /* 子进程 */
        while (1)
        {
            printf("l am child\n");
            sleep(1);
        }
    }
    else 
    {   
        /* 父进程 */
        sleep(1);
        
        int ret = kill(pid, SIGKILL);
        if (ret == -1)
        {
            perror("kill error");
            exit(-1);
        }

        /* 回收资源 */
        wait(NULL);
    }


    return 0;
}