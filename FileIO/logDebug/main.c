#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdbool.h>


bool g_debug = 0;

FILE * g_fp = NULL;



#define LOGPR(fmt, args...)             \
    do                                  \
    {                                   \
        if (g_debug)                    \
        {                               \
            time_t now;                 \
            struct tm *ptm = NULL;      \
            now = time(NULL);           \
            ptm = localtime(&now);      \
            fprintf(g_fp, "[file:(%s), func(%s), line(%d), time(%s)]:\n" fmt, \
                __FILE__, __FUNCTION__, __LINE__, asctime(ptm), ##args);    \
            fflush(g_fp);                                                   \
        }                                                                   \
    } while (0);
    
/* 开启日志 */
void log_init()
{
    time_t now;
    struct tm *ptm = NULL;
#define DEBUG_FLAG  "./my_debug.flag"

    if (access(DEBUG_FLAG, F_OK) == 0)
    {
        g_debug = 1;
    }

    if (!g_debug)
    {
        return;
    }

#define DEBUG_FILE "/var/log/testmain.log"

    if ((g_fp = fopen(DEBUG_FILE, "a")) == NULL)
    {
        perror("fopen error");
        return;
    }

    now = time(NULL);
    ptm = localtime(&now);



    LOGPR("===============log init done.======\n");

    return;
}

/* 关闭日志 */
void log_close()
{
    if (g_fp != NULL)
    {
        fclose(g_fp);
    }
}

int main()
{

    log_init();

    int val = 666;
    LOGPR("val = %d\n", val);

    log_close();
    return 0;
}