/*************************************************************************
	> File Name: test_recv_client.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年09月08日 星期二 22时20分37秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define IP "127.0.0.1"

#define PORT 8888 

#define EXIT       0
#define LOGIN      1
#define REGIST     2

typedef struct package {
        int  type;
        int  account;
        char send_name[100];
        int  send_account;
        time_t time;
        char mes[1000];
        char mes2[1000];

} PACK;
int send_login_PACK(int );
void send_regist_PACK(int);

int main()
{
        int cli_fd;
        struct sockaddr_in serv_addr;
        
        cli_fd = socket(AF_INET, SOCK_STREAM, 0);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        serv_addr.sin_addr.s_addr = inet_addr(IP);
        
        if(connect(cli_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1)
    {
                perror("connect 出现问题");
                exit(-1);
            
    }
        printf("客户端启动成功");
        send_login_PACK(cli_fd);
        send_regist_PACK(cli_fd);
        sleep(5);
}

int send_login_PACK(int conn_fd)
{
    
        PACK pack; 
        pack.type = LOGIN;
    if(send(conn_fd, &pack, sizeof(PACK),0)<0){
                perror("send");
    }
    printf("1 = %d\n", conn_fd);                        

}  

void send_regist_PACK(int conn_fd)
{
        PACK pack;
        pack.type = REGIST;
        int cli_fd;
        struct sockaddr_in serv_addr;
        
        cli_fd = socket(AF_INET, SOCK_STREAM, 0);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        serv_addr.sin_addr.s_addr = inet_addr(IP);
        
        if(connect(cli_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1)
    {
                perror("connect 出现问题");
                exit(-1);
    } 
    int i = 0;

        if(send(cli_fd, &pack, sizeof(PACK),0)<0){
                perror("send");
    }
    pack.type = 3;
    while(i < 10) {
        pack.account = i++;
        if(send(cli_fd, &pack, sizeof(PACK),0)<0){
                perror("send");
    }
    
    printf("2 = %d\n", i);
    }

}
