#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/* 面包 */
int g_data = 10;

/* 锁 🔒*/
pthread_mutex_t g_mutex;
pthread_cont_t g_cond;

#if 0
void * thread_func1(void *arg)
{
	while (g_data > 0)
	{
		/* 客气一下 */
		usleep(10);

		g_data--;
		printf("thread1... gdata:%d\n", g_data);
	}
}

void * thread_func2(void *arg)
{
	while (g_data > 0)
	{
		/* 假装客气一下 */
		usleep(5);

		g_data--;
		printf("thread2... gdata:%d\n", g_data);
	}
}

void * thread_func3(void *arg)
{
	while (g_data > 0)
	{
		/* 假装客气一下 */
		usleep(7);

		g_data--;
		printf("thread3... gdata:%d\n", g_data);
	}
}
#endif

// 打印机，公共资源
void printer(char *str)
{
    pthread_mutex_lock(&g_mutex);
    while (*str != '\0')
    {
        putchar(*str);
        fflush(stdout);
        str++;
        sleep(1);
    }
    pthread_mutex_unlock(&g_mutex);
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
	pthread_mutex_init(&g_mutex, NULL);

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

	pthread_mutex_destroy(&g_mutex);
	return 0;
}
