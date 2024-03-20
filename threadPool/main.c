#include <stdio.h>
#include "threadPool.h"
#include <unistd.h>
#include <string.h>

void * printInfo(void * arg)
{
    int val = *(int *)arg;
    sleep(1);
    printf("val = %d\n", val);
};

int main()
{
    ThreadPool pool;
    memset(&pool, 0, sizeof(pool));

    /* 线程池初始化 */
    threadPoolInit(&pool, 3, 10, 50);

    int nums[100] = { 0 };
    for (int idx = 1; idx <= 100; idx++)
    {
        nums[idx] = idx;
        threadPoolAdd(&pool, printInfo, &nums[idx]);
    }

    while (1)
    {
        sleep(3);
    }



    return 0;
}