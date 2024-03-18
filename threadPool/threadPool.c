#include "threadPool.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    MALLOC_ERROR,
    NULL_PTR,
    INVALID_ACCESS,
};

#define TIME_INTERVAL   5
#define DEFAULT_THREAD_NUM  10
#define PER_NUMBER      3


/* 工作线程 */
static void * thread_worker(void *arg)
{
    pthread_detach(pthread_self());

    ThreadPool *pool = (ThreadPool *)arg;

    while (true)
    {
        /* 加锁 */
        pthread_mutex_lock(&pool->mutex);
        while (pool->queueSize == 0)
        {
            /* 等待条件变量 */
            pthread_cond_wait(&pool->queueBusy, &pool->mutex);
        }
        /* 程序到这个地方 有任务 */
        /* 从任务队列中取任务 */
        Task_t newTask;
        newTask.func = pool->queue[pool->queueFront].func;
        newTask.arg = pool->queue[pool->queueFront].arg;
        /* 移动队头位置 */
        pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
        /* 任务队列 任务数减一. */
        pool->queueSize--;

        /* 解锁 */
        pthread_mutex_unlock(&pool->mutex);
        pthread_cond_signal(&pool->queueFree);


        pthread_mutex_lock(&pool->busyMutex);
        pool->busy_thread_num++;
        pthread_mutex_unlock(&pool->busyMutex);

        /* 处理任务 */
        newTask.func(newTask.arg);

        pthread_mutex_lock(&pool->busyMutex);
        pool->busy_thread_num--;
        pthread_mutex_unlock(&pool->busyMutex);
    }

    pthread_exit(NULL);
}


/* 任务调度 */
static void * thread_manage(void *arg)
{
    pthread_detach(pthread_self());

    ThreadPool *pool = (ThreadPool *)arg;

    while (1)
    {
        sleep(TIME_INTERVAL);

        /* 取出线程池中的 任务队列的任务个数 */
        pthread_mutex_lock(&pool->mutex);
        int queueSize = pool->queueSize;
        pthread_mutex_unlock(&pool->mutex);

        /* 当前忙的线程 */
        pthread_mutex_lock(&pool->busyMutex);
        int busy_thread_num = pool->busy_thread_num;
        pthread_mutex_unlock(&pool->busyMutex);


        /* 什么时候需要增加线程池中的线程数? */
        /* 任务队列的任务远远大于 忙碌的线程数 */

        if (queueSize > busy_thread_num)
        {
            /* todo... 后面做解释 */
            pthread_mutex_lock(&(pool->mutex));
            int count = 0;
            for (int idx = 0; idx < pool->max_thread_num && count < PER_NUMBER; idx++)
            {
                if (pool->threadIds[idx] == 0)
                {
                    pthread_create(&pool->threadIds[idx], NULL, thread_worker, pool);
                    count++;
                    pool->alive_thread_num++;
                }
            }
            pthread_mutex_unlock(&(pool->mutex));
        }


        /* */








    }
}

/* 线程池初始化 */
int threadPoolInit(ThreadPool * pool, int threadMinThread, int threadMaxThreads, int queueCapacity)
{
    if (pool == NULL)
    {
        return NULL_PTR;
    }

    if (threadMaxThreads <= 0)
    {
        threadMaxThreads = DEFAULT_THREAD_NUM;
    }
    pool->max_thread_num = threadMaxThreads;

    /* 条件变量 和 锁 资源初始化 */
    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_mutex_init(&(pool->busyMutex), NULL);
    pthread_cond_init(&(pool->queueBusy), NULL);
    pthread_cond_init(&(pool->queueFree), NULL);

    
    /* 初始化队列相关属性 */
    pool->queueSize = 0;
    pool->queueCapacity = queueCapacity;
    pool->queueFront = 0;
    pool->queueRear = 0;

    /* 任务队列初始化 */
    pool->queue = (Task_t *)malloc(sizeof(Task_t) * pool->queueCapacity);
    if (pool->queue == NULL)
    {
        perror("malloc error");
        exit(-1);
    }

    pool->threadIds = (pthread_t *)malloc(sizeof(pthread_t) * threadMaxThreads);
    if (pool->threadIds == NULL)
    {
        perror("malloc error");
        exit(-1);
    }
    /* 清除脏数据 */
    memset(pool->threadIds, 0, sizeof(pthread_t) * threadMaxThreads);


    int ret = pthread_create(&pool->managerId, NULL, thread_manage, pool);
    if (ret == -1)
    {
        perror("thread create error");
        exit(-1);
    }

    pool->alive_thread_num = 0;
    for (int idx = 0; idx < threadMinThread; idx++)
    {
        ret = pthread_create(&pool->threadIds[idx], NULL, thread_worker, pool);
        if (ret == -1)
        {
            perror("thread create error");
            exit(-1);
        }
        pool->alive_thread_num++;
    }
}


/* 添加任务 */
int threadPoolAdd(ThreadPool * pool, void * (*func)(void * arg), void * arg)
{
    if (pool == NULL)
    {
        return NULL_PTR;
    }

    /* 上锁🔒 */
    pthread_mutex_lock(&pool->mutex);
    while (pool->queueSize == pool->queueCapacity)
    {
        pthread_cond_wait(&(pool->queueFree), &pool->mutex);
    }
    /* 程序到这里, 说明什么? */
    pool->queue[pool->queueRear].func = func;
    pool->queue[pool->queueRear].arg = arg;
    pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;
    pool->queueSize++;

    /* 解锁 */
    pthread_mutex_unlock(&pool->mutex);
    pthread_cond_signal(&pool->queueBusy);

    return ON_SUCCESS;
}






