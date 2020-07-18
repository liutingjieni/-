/*************************************************************************
	> File Name: pipe.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年07月18日 星期六 10时01分08秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd[2];
    char str[256];
    if (pipe(fd) < 0) {
        puts("create the pipe failed!\n");
        exit(1);
    }
    write(fd[1], "create the pipe successfully!", 31);
    read(fd[0], str, sizeof(str));
    printf("%s\n", str);
    printf("pipe file descriptors are %d, %d\n", fd[0], fd[1]);
    sleep(20);
    close(fd[0]);
    close(fd[1]);
    return 0;
}
