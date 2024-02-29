#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 32

int main()
{
    const char * name = "./test.txt";
    
    struct stat bufferStat;
    memset(&bufferStat, 0, sizeof(bufferStat));
    stat(name, &bufferStat);

    /* 文件大小 */
    printf("size:%ld\n", bufferStat.st_size);
    /* 文件类型 : 普通文件 */
    printf("mode:%d\n", S_ISREG(bufferStat.st_mode));


    /* 时间打印 */
    localtime(&(bufferStat.st_atime));
    printf("atime:%s\n", ctime(&(bufferStat.st_atime)));

    localtime(&(bufferStat.st_mtime));
    printf("mtime:%s\n", ctime(&(bufferStat.st_mtime)));

    localtime(&(bufferStat.st_ctime));
    printf("ctime:%s\n", ctime(&(bufferStat.st_ctime)));

    return 0;
}