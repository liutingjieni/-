/*************************************************************************
	> File Name: threadpool.h
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年02月20日 星期四 04时28分38秒
 ************************************************************************/

#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include <semaphore.h>

class sem {
public:
    sem()
    {
        if (sem_init( &m_sem, 0, 0 ) != 0) {
            printf("1");
            throw std::exception();
        }
    }
    ~sem() { sem_destroy(&m_sem); }
    bool wait() { return sem_wait(&m_sem) == 0; }
    bool post() { return sem_post(&m_sem) == 0; }
private:
    sem_t m_sem;
};

class locker {
public:
    locker()
    {
        if (pthread_mutex_init(&m_mutex, NULL) != 0) {
            printf("2");
            throw std::exception();
        } 
    }
    ~locker() { pthread_mutex_destroy(&m_mutex); }
    bool lock() { return pthread_mutex_lock(&m_mutex) == 0; }
    bool unlock() { return pthread_mutex_unlock(&m_mutex) == 0; }
private:
    pthread_mutex_t m_mutex;
};

template <typename T>
class threadpool {
public:
    threadpool(int thread_number = 8, int max_requests = 10000);
    ~threadpool();

    bool append(T * request);
private:
    static void *worker(void *arg);
    void run();

    int m_thread_number;
    int m_max_requests;
    pthread_t *m_threads;
    std::list<T *> m_workqueue;
    locker m_queuelocker;
    sem m_queuestat;
    bool m_stop;
};

template <typename T>
threadpool<T>::threadpool(int thread_number, int max_requests):
    m_thread_number(thread_number), m_max_requests(max_requests),
    m_stop(false), m_threads(NULL)
{
    if ((thread_number <= 0) || max_requests <= 0) {
        throw std::exception();
    }
    m_threads = new pthread_t[m_thread_number];
    if (!m_threads) {
        throw std::exception();
    }

    for (int i = 0; i < thread_number; i++) {
        if (pthread_create(m_threads + i, NULL, worker, this) != 0) {
            delete [] m_threads;
            throw std::exception();
        }
        if (pthread_detach(m_threads[i])) {
            delete [] m_threads;
            throw std::exception();
        }
    }
}


template <typename T> 
threadpool<T>:: ~threadpool()
{
    delete [] m_threads;
    m_stop = true;
}

template <typename T>
bool threadpool<T>::append(T *request)
{
    m_queuelocker.lock();
    if (m_workqueue.size() > m_max_requests) {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back(request);
    m_queuelocker.unlock();
    m_queuestat.post();
    return true;
}

template <typename T>
void *threadpool<T>::worker(void *arg)
{
    threadpool *pool = (threadpool *)arg;
    pool->run();
    return pool;
}

template <typename T>
void threadpool<T>::run()
{
    while (!m_stop) {
        m_queuestat.wait();
        m_queuelocker.lock();
        if (m_workqueue.empty()) {
            m_queuelocker.unlock();
            continue;
        }
        T *request = m_workqueue.front();
        m_workqueue.pop_front();
        m_queuelocker.unlock();
        if (!request) {
            continue;
        }
        request->process();
    }
}
#endif
