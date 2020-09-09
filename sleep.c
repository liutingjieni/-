/*************************************************************************
	> File Name: sleep.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年07月18日 星期六 11时06分02秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_fun(void *arg)
{
    printf("llllllllll\n");
    sleep(20);
    printf("ppppp\n");
}


int main()
{
    pthread_t tid1;
    pthread_create(&tid1, NULL, thread_fun, NULL);
    sleep(10);
}
