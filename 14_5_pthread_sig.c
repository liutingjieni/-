/*************************************************************************
	> File Name: 14_5_pthread_sig.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年02月17日 星期一 02时04分18秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define handle_errno_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0);

static void *sig_thread(void *arg)
{
    sigset_t *set = (sigset_t *)arg;
    int s, sig;
    for (;;) {
        s = sigwait(set, &sig);
        if (s != 0) {
            handle_errno_en(s, "sigwait");
        }
        printf("Signal handing thread got signal %d\n", sig);
    }
}

int main()
{
    pthread_t thread;
    sigset_t set;
    int s;

    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGUSR1);
    s = pthread_sigmask(SIG_BLOCK, &set, NULL);
    if (s != 0) {
        handle_errno_en(s, "pthread_sigmask");
    }

    s = pthread_create(&thread, NULL, &sig_thread, (void *)&set);
    if (s != 0) {
        handle_errno_en(s, "pthread_create");
    }

    pause();

}
