#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define BUFFER_SIZE 128

int main()
{
    const char * name = "/home/257class/BasiC/257-operation-system/FileIO/testDIR/music";
    
    char buffer[BUFFER_SIZE] = { 0 };
    getcwd(buffer, BUFFER_SIZE - 1);
    printf("buffer:%s\n", buffer);
    
    DIR * dir = opendir(name);
    if (dir == NULL)
    {
        perror("opendir error");
        return -1;
    }

    /* 文件夹打开成功 */
    struct dirent * musicdir = NULL;
    while ((musicdir = readdir(dir)) != NULL)
    {
        if (musicdir->d_type != DT_DIR)
        {
            printf("d_type:%d,\td_name:%s\n", musicdir->d_type, musicdir->d_name);
        }
    }
    /* 关闭文件夹 */
    closedir(dir);
    return 0;
}