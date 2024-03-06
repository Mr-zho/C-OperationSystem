#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/* 面包 */
int g_data = 10;

/* 锁 资源 */
pthread_mutex_t g_mutex;
/* 条件变量 资源 */
pthread_cond_t g_freePlate;
pthread_cond_t g_enoughPie;

/* 链表 */
typedef struct Node
{
	int data;
	struct Node * next;
}Node;
/* 链表头结点 */
Node * head = NULL;
int g_pieCnt = 0;
/* 常量 */
const int maxPlates = 8;

/* 生产者 : 做饼 */
void * thread_produce(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&g_mutex);
		/* 当前饼的数量 已经等于盘子的数量 */
		while (g_pieCnt == maxPlates)
		{
			pthread_cond_wait(&g_freePlate, &g_mutex);
		}
		/* 程序到这个地方 : 有空闲的盘子了 */

		/* 创建一个链表结点 (饼) */
		Node * newPie = malloc(sizeof(Node) * 1);
		newPie->data = rand() % 999 + 1; // 1 ~ 999
		
		/* 头插 */
		newPie->next = head;
		head = newPie;
		printf("producer make %d pie\n", newPie->data);
		/* 当前已经有的饼加一. */
		g_pieCnt++;

		pthread_mutex_unlock(&g_mutex);
		pthread_cond_signal(&g_enoughPie);
		
		/* 休息2S */
		sleep(1);
	}
}

/* 消费者 : 吃饼 */
void * thread_consume(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&g_mutex);
		while (g_pieCnt == 0)
		{
			pthread_cond_wait(&g_enoughPie, &g_mutex);
		}
		/* 程序到这个地方说明: 有饼吃 */

		Node * pie = head;
		head = head->next;
		printf("tid:%ld,\tconsumer eat %d pie\n", pthread_self(), pie->data);
		
		/* 释放内存 */
		if (pie != NULL)
		{
			free(pie);
			pie = NULL;
		}
		/* 饼减一. */
		g_pieCnt--;
		pthread_mutex_unlock(&g_mutex);
		pthread_cond_signal(&g_freePlate);
	}
}



int main()
{
	/* 初始化锁 */
	pthread_mutex_init(&g_mutex, NULL);
	/* 初始化条件变量 */
	pthread_cond_init(&g_freePlate, NULL);
	pthread_cond_init(&g_enoughPie, NULL);

	pthread_t tid1, tid2, tid3;
	int ret = pthread_create(&tid1, NULL, thread_produce, NULL);
	if (ret == -1)
	{
		printf("pthread_create error\n");
		exit(-1);
	}	

	ret = pthread_create(&tid2, NULL, thread_consume, NULL);
	if (ret == -1)
	{
		printf("pthread_create error\n");
		exit(-1);
	}	

	ret = pthread_create(&tid3, NULL, thread_consume, NULL);
	if (ret == -1)
	{
		printf("pthread_create error\n");
		exit(-1);
	}	

	while(1)
	{
		sleep(1);
	}
	return 0;
}
