/*************************************************************************
	> File Name: CGI.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年02月03日 星期一 01时28分13秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100

int main()
{
    char *buf;
    char *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1 = 0, n2 =0;

    if ((buf = getenv("QUERY_STRING")) != NULL) {
        p = strchr(buf, '&');
        *p = '\0';
        strcpy(arg1, buf);
        strcpy(arg2, p + 1);
        n1 = atoi(arg1);
        n2 = atoi(arg2);
    }

    sprintf(content, "QUERY_STRING = %s", buf);
    sprintf(content, "Welcome to add.com: ");
    sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
    sprintf(content, "%sThe answer is: %d + %d= %d\r\n<p>",
           content, n1, n2, n1 + n2);
    sprintf(content, "%sThanks for visiting!\r\n", content);

    printf("Connection: close\r\n");
    printf("Content-length: %d \r\n", (int)strlen(content));
    printf("content-type: text/html\r\n\r\n");
    printf("%s",content);
    fflush(stdout);

    exit(0);
}
