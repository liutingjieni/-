/*************************************************************************
	> File Name: 12_1_libevent.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年02月07日 星期五 16时12分49秒
 ************************************************************************/

#include <stdio.h>
#include <sys/signal.h>
#include <event.h>

void signal_cb(int fd, short event, void *argc)
{
    struct event_base *base = ( struct event_base *)argc;
    struct timeval delay = {2, 0};
    printf("Caught an interrupt signal; exiting cleanly in two seconds\n");
    event_base_loopexit(base, &delay);
}

void timeout_cb(int fd, short event, void *argc)
{
    printf("timeout\n");
}

int main()
{
    struct event_base *base = event_init();

    struct event *signal_event = event_new(base, SIGINT,EV_SIGNAL |  EV_PERSIST, signal_cb, base);
    event_add(signal_event, NULL);

    struct timeval tv = {1, 0};
    struct event *timeout_event = evtimer_new(base, timeout_cb, NULL);
    event_add(timeout_event, &tv);

    event_base_dispatch(base);

    event_free(timeout_event);
    event_free(signal_event);
    event_base_free(base);
}
