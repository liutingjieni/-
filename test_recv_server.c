/*************************************************************************
	> File Name: test_recv_server.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年09月08日 星期二 22时15分44秒
 ************************************************************************/

#include <stdio.h>

#include <pthread.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
 #define SERV_PORT       8888
 #define IP              "0.0.0.0" 
 #define EPOLL_MAX       10000
 #define LISTENMAX       1000
#include <time.h>

#define EXIT       0
#define LOGIN      1
#define REGIST     2
#define REPASSWD   3
#define ADD_FRIEND 4
#define LIST_FRI   5
#define ONLINE_FRI 6
#define CHAT_FRI   7
#define STORE_CHAT 8
#define DELE_FRI   9
#define CREAT_GROUP 10
#define JOIN_GROUP  11
#define QUIT_GROUP  12
#define DELE_GROUP  13
#define GROUP_MES   14
#define CHAT_GROUP  15
#define STORE_G     16
#define SET_UP      17
#define SEND_FILE   18
#define OK_FILE     19
#define JOIN_USER   20
#define DELE_USER   21

typedef struct package {
        int  type;
        int  account;
        char send_name[100];
        int  send_account;
        time_t time;
        char mes[1000];
        char mes2[1000];

} PACK;

typedef struct friends {  //好友列表
                           int  account[50];
                           char name[50][100];
                           int online[50];
                           int  len;
                       }fri;

typedef struct store_chat { //私聊记录
                              int account[100];
                              int send_account[100];
                              char mes[100][1000];
                              int len;
                          }STR;

typedef struct group {  //群信息
                         int account[50];
                         char name[50][100];
                         int online[50];
                         int cli_fd[50];
                         int flag[50];
                         int len;
                     }GROUP;

typedef struct store_group {
        int usr_account[100];
        char use_name[100][100];
        char mes[100][1000];
        int len;

}STR_G;


 void my_err(const char * err_string,int line)
 {
        fprintf(stderr, "line:%d  ", line);
        perror(err_string);
        exit(1);

 }

 int init()
 {
         int sock_fd,epoll_fd,fd_num,conn_fd;
         struct sockaddr_in serv_addr;
         struct sockaddr_in cli_addr;
         struct epoll_event ev, events[LISTENMAX];
         int cli_len = sizeof(struct sockaddr_in);

         
         sock_fd = socket(AF_INET, SOCK_STREAM, 0);
         if (sock_fd < 0)
     {
                 perror("创建socket失败");
                 exit(-1);
             
     }

         int optval = 1;
         if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(int))<0)
     {
                 perror("套接字重新绑定失败");

             
     }

         memset(&serv_addr, 0,sizeof(struct sockaddr_in));
         serv_addr.sin_family =  AF_INET;
         serv_addr.sin_port = htons(SERV_PORT);
         serv_addr.sin_addr.s_addr = inet_addr(IP);
         
         if (bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in))<0)
     {
                 perror("绑定失败");
                 exit(-1);
             
     }
         
         epoll_fd = epoll_create(EPOLL_MAX);//生成epoll句柄
         ev.data.fd = sock_fd;//设置与要处理事件相关的文件描述符
         ev.events = EPOLLIN;//设置要处理的事件类型
         epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &ev);//注册epoll事件


         if (listen(sock_fd, 10) < 0)
     {
                 perror("设置监听失败");
                 exit(-1);
             
     }
         printf("listen success\n");
         while(1)
 {
             fd_num = epoll_wait(epoll_fd, events, EPOLL_MAX, 1000);
             for (int i = 0; i < fd_num; i++)
     {
                     if (events[i].data.fd == sock_fd)
         {
                             conn_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, &cli_len);
                             if (conn_fd < 0)
             {
                                     perror("连接失败");
                                 
             }
                             ev.data.fd = conn_fd;
                             ev.events = EPOLLIN;
                             epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev);

                         
         }
                     else if (events[i].events & EPOLLIN)
         {
                            recv_PACK(events[i].data.fd);
                            //n = recv(events[i].data.fd, &recv_t, sizeof(PACK), 0);
             //                // recv_t.data.send_fd = events[i].data.fd;
             //                            
         }
                 
     }
         
 }



 }
void recv_PACK(int conn_fd)
{
        PACK pack;
        cli_fd = conn_fd;
        int ret;
    if((ret = recv(cli_fd, &pack,sizeof(PACK) ,MSG_WAITALL)) < 0) {
                perror("server_recv");
            
    }
        int type = pack.type;
        switch (type)
    {
               
                case 1:
                    printf("%d\n", pack.type);
                    break;
                case 2:
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, conn_fd, &ev);//注册epoll事件
                    recv(cli_fd, &pack,sizeof(PACK) ,MSG_WAITALL);
                        printf("cli_fd = %d\n", cli_fd); 
                    
    }
}
