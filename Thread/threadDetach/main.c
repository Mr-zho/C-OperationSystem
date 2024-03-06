#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>

void * thread_func(void *arg)
{
	pthread_detach(pthread_self());	
	printf("new thread:%ld\n", pthread_self());

	while (1)
	{
		printf("l am thread...\n");
		sleep(1);
	}
	
	/* 线程退出 */
	int retStatus = -45;
#if 0
	int * retStatus = (int *)malloc(sizeof(int) * 1);
	*retStatus = -45;
#endif
	pthread_exit(&retStatus);

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

	/* 这边的延时操作是为了让子线程先分离 */
	sleep(1);

	/* 阻塞等待回收子线程的资源 */ 
	int * retStatus = NULL;
	ret = pthread_join(tid, (void **)&retStatus);
	printf("ret = %d\n", ret);
	
	if (ret == EINVAL)
	{
		printf("detached...\n");
	}
	int cnt = 5;
	while (cnt--)
	{
		printf("main thread\n");
		sleep(1);
	}	

	if (retStatus)
	{
		/* 解引用 */
		printf("retStatus:%d\n", *retStatus);
	}
	return 0;
}
