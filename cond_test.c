/*************************************************************************
	> File Name: cond_test.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年07月27日 星期一 23时10分54秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>

int ready = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *threadA(void *arg)
{
    pthread_mutex_lock(&mutex);
    if (0 == ready) {
        
        //释放有mutex指向的互斥锁,同时使当前线程关于cond指向的条件变量阻塞,直到条件被信号唤醒
        pthread_cond_wait(&cond, &mutex);

    }
    pthread_mutex_unlock(&mutex);
}

void *threadB(void *arg)
{
    pthread_mutex_lock(&mutex);
    ready = 1;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, threadA, NULL);
    pthread_create(&tid, NULL, threadB, NULL);
    
    pthread_join(tid, NULL);
}
