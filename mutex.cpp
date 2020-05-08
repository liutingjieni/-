/*************************************************************************
	> File Name: mutex.cpp
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年05月08日 星期五 16时05分24秒
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <exception>

using namespace std;

int a = 0;

class locker {
public:
    locker()
    {
        if (pthread_mutex_init(&m_mutex, NULL) != 0) {
                        throw std::exception();                   
        }             
    }
    ~locker() { pthread_mutex_destroy(&m_mutex); }
    bool lock() { return pthread_mutex_lock(&m_mutex) == 0; }     
    bool unlock() { return pthread_mutex_unlock(&m_mutex) == 0; }
private:
    pthread_mutex_t m_mutex;
};

locker mutex_t;

void *thread_fun(void *arg)
{
    printf("thread_fun1 %d\n",a);
    mutex_t.lock();
    //printf("thread_fun1 %d\n",a);
    a--;
    mutex_t.unlock();
    printf("thread_fun2 %d\n",a);
}

int main()
{
    pthread_t id;
    pthread_create(&id, NULL, thread_fun, NULL);
    printf("%d\n",a);
    mutex_t.lock();
    a++;
    //sleep(5);   //主线程加锁，子线程会等待主线程解锁后加锁。
    mutex_t.unlock();
    printf("%d\n",a);
    pthread_join(id, NULL);
}
