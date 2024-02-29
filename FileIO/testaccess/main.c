#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 32

int main()
{
    const char * name = "./tet.txt";
    
    /* 判断文件是否存在 */
    int ret = access(name, F_OK);
    printf("ret:%d\n", ret);

    /* 判断文件是否有读权限 */
    ret = access(name, R_OK);
    printf("ret:%d\n", ret);

    /* 判断文件是否有写权限 */
    ret = access(name, W_OK);
    printf("ret:%d\n", ret);

    /* 判断文件是否存在有执行权限 */
    ret = access(name, X_OK);
    printf("ret:%d\n", ret);

    return 0;
}