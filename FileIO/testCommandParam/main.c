#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 32

int main(int argc, const char *argv[])
{
    printf("argc:%d\n", argc);

    for (int idx = 0; idx < argc; idx++)
    {
        printf("argv[%d] = %s\n", idx, argv[idx]);
    }
    
    printf("hello world\n");
    return 0;
}