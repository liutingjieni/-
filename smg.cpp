/*************************************************************************
	> File Name: smg.cpp
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年05月08日 星期五 14时14分15秒
 ************************************************************************/

#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *_buf;
};

void pv(int sem_id, int op)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = op;
    sem_b.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_b, 1);
}

int main()
{
    int sem_id = semget(IPC_PRIVATE, 1, 0666);

    union semun sem_un;
    sem_un.val = 1;
    semctl(sem_id, 0, SETVAL, sem_un);

    pid_t id = fork();
    if (id < 0) {
        return 1;
    }
    else if (id == 0) {
        printf("child try to get binary sem\n");
        pv(sem_id, -1);
        printf("child get the sem and would release it after 5 seconds\n");
        sleep(5);
        pv(sem_id, 1);
        exit(0);
    }
    else {
        printf("parent try to get binary sem\n");
        pv(sem_id, -1);
        printf("parent get the sem and would release it after 5 seconds\n");
        sleep(5);
        pv(sem_id, 1);
        printf("lala\n");
    }
    waitpid(id, NULL, 0);
    semctl(sem_id, 0, IPC_RMID, sem_un);
    return 0;
}

/*
 * struct sembuf{
 *     short sem_num; // 除非使用一组信号量，否则它为0
 *     short sem_op;  // 信号量在一次操作中需要改变的数据，通常是两个数，一个是-1，即P（等待）操作，
 *                    // 一个是+1，即V（发送信号）操作。
 *     short sem_flg; // 通常为SEM_UNDO,使操作系统跟踪信号，
 *                    // 并在进程没有释放该信号量而终止时，操作系统释放信号量
 *};
*/
