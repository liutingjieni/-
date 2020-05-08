/*************************************************************************
	> File Name: cond.cpp
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年05月08日 星期五 21时22分45秒
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <exception>
using namespace std;

class cond {
public:
    cond() {
        if (pthread_mutex_init(&m_mutex, NULL) != 0) {
            throw std::exception();
                    
        }
        if (pthread_cond_init(&m_cond, NULL) != 0) {
            pthread_mutex_destroy(&m_mutex);
            throw std::exception();
                    
        }    
    }
    ~cond()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_cond);
            
    }
    bool wait()
    {
        int ret = 0;
        pthread_mutex_lock(&m_mutex);
        ret = pthread_cond_wait(&m_cond, &m_mutex);
        pthread_mutex_unlock(&m_mutex);
        return ret = 0;    
    }
    bool signal() {
        return pthread_cond_signal(&m_cond) == 0;    
    }
private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

cond cond_t;

void *thread_fun(void *arg)
{
    cond_t.wait();
    printf("child thread is signal\n");
}

int main()
{
    pthread_t id;
    pthread_create(&id, NULL, thread_fun, NULL);
    int a = 1;
    if (a) {
        sleep(1);
        cond_t.signal();
        printf("signal\n");
    }
    pthread_join(id, NULL);
}
