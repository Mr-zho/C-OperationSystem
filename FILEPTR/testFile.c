#include <stdio.h>

int main()
{
    const char * name = "test.txt";
    FILE * fp = fopen(name, "w+");
    if (fp == NULL)
    {
        perror("fopen error\n");
        return -1;
    }
    
    char buffer[] = "hello world\n";
    fwrite(buffer, 1, sizeof(buffer), fp);

    
    /* 关闭文件 */
    fclose(fp);
    return 0;
}