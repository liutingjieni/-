/*************************************************************************
	> File Name: sigalrm.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年10月19日 星期一 18时41分46秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int t = 0;

void fun(int signal)
{
    printf("seconds: %d", ++t);
    alarm(1);
}

int main()
{
    if (signal(SIGALRM, fun) == SIG_ERR) {
        perror("signal");
        return 0;
    }
    setbuf(stdout, NULL);
    alarm(1);
    while(1) {
        pause();
    }
}
