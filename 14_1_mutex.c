/*************************************************************************
	> File Name: 14_1_mutex.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年02月16日 星期日 17时04分57秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int a = 0;
int b = 0;
pthread_mutex_t mutex_a;
pthread_mutex_t mutex_b;

//去掉sleep的注释会形成死锁

void *another(void *arg)
{
    pthread_mutex_lock(&mutex_b);
    printf("in child thread, got mutex b, waiting for mutex a\n");
    //sleep(5);
    ++b;
    pthread_mutex_lock(&mutex_a);
    b += a++;
    pthread_mutex_unlock(&mutex_a);
    pthread_mutex_unlock(&mutex_b);
    pthread_exit(NULL);
}

int main()
{
    pthread_t id;

    pthread_mutex_init(&mutex_a, NULL);
    pthread_mutex_init(&mutex_b, NULL);
    
    //id是新线程的标识符, 第二个参数用于设置新线程的属性
    pthread_create(&id, NULL, another, NULL);

    pthread_mutex_lock(&mutex_a);
    printf("in parent thread, got mutex a, waiting for mutex b\n");
    //sleep(5);
    ++a;
    pthread_mutex_lock(&mutex_b);
    a += b++;
    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);

    //回收其他线程,id是目标线程的标识符,第二个参数是目标线程返回的退出信息
    pthread_join(id, NULL);
    //销毁互斥锁
    pthread_mutex_destroy(&mutex_a);
    pthread_mutex_destroy(&mutex_b);

    return 0;
}
