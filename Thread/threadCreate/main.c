#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void * thread_func(void *arg)
{
	
	printf("new thread:%ld\n", pthread_self());

	sleep(50);
}
int main()
{
	pthread_t tid;
	
	int ret = pthread_create(&tid, NULL, thread_func, NULL);	
	if (ret != 0)
	{
		printf("pthread_create error\n");
		exit(-1);
	}
	printf("main thread:%ld\n", pthread_self());

	sleep(60);
	return 0;
}
