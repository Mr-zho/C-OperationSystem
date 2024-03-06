#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

/* 面包 */
int g_data = 10;

/* 信号量 */
sem_t g_sem;

// 打印机，公共资源
void printer(char *str)
{
    sem_wait(&g_sem);	// 减一
    while (*str != '\0')
    {
        putchar(*str);
        fflush(stdout);
        str++;
        sleep(1);
    }
    sem_post(&g_sem);	// 加一
    printf("\n");
}

// 线程一
void *thread_func1(void *arg)
{
    char *str = "hello";
    printer(str); //打印
}

// 线程二
void *thread_func2(void *arg)
{
    char *str = "world";
    printer(str); //打印
}


int main()
{
	/* 初始化锁 */
	sem_init(&g_sem, 0, 1);
	pthread_t tid1, tid2, tid3;
	int ret = pthread_create(&tid1, NULL, thread_func1, NULL);
	if (ret == -1)
	{
		printf("pthread_create error\n");
		exit(-1);
	}	

	ret = pthread_create(&tid2, NULL, thread_func2, NULL);
	if (ret == -1)
	{
		printf("pthread_create error\n");
		exit(-1);
	}	

#if 0	
	ret = pthread_create(&tid3, NULL, thread_func3, NULL);
	if (ret == -1)
	{
		printf("pthread_create error\n");
		exit(-1);
	}	
#endif

	while(1)
	{
		sleep(1);
	}

	return 0;
}
