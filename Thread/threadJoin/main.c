#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void * thread_func(void *arg)
{
	
	printf("new thread:%ld\n", pthread_self());

	sleep(1);
	
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

	printf("tid:%ld\n", tid);
	printf("main thread:%ld\n", pthread_self());
	
	/* 阻塞等待回收子线程的资源 */ 
	int * retStatus = NULL;
	pthread_join(tid, (void **)&retStatus);
	
	/* 解引用 */
	printf("retStatus:%d\n", *retStatus);
	return 0;
}
