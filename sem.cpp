/*************************************************************************
	> File Name: sem.cpp
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年05月08日 星期五 15时15分40秒
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <exception>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

class sem {
public:
    sem()
    {
        if (sem_init( &m_sem, 0, 1  ) != 0) {
            throw std::exception();
                    
        }
            
    }
    ~sem() { sem_destroy(&m_sem);  }
    bool wait() { return sem_wait(&m_sem) == 0;  }
    bool post() { return sem_post(&m_sem) == 0;  }
private:
    sem_t m_sem;
};


void *thread_fun(void *arg)
{
    printf("child thread\n");
    sem sem_t;
    sem_t.wait();
    printf("main thread 5 seconds ,post after\n");
    sem_t.post();
}

int main()
{
    pthread_t id;
    sem sem_t;
    pthread_create(&id, NULL, thread_fun, NULL);
    printf("main thread\n");
    sem_t.wait();
    sleep(2);
    sem_t.post();
}
