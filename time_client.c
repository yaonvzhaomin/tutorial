#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <stdarg.h>
#include <fcntl.h>


int main()
{
    int sockfd;
    int len;
    char buff[100];
    struct sockaddr_in serveraddr;
    
    bzero(&serveraddr, sizeof(serveraddr));
    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port   = htons(8888);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
        return -1; 
    }
    
    if( connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))<0 )
    {
        perror("connect error");
        return -1;
    }
    
    len = read(sockfd, buff, 100);
    
    if( len < 0 )
    {
        printf("Error ,read fail.\n");
        return -1;
    }
    
    if( len == 0 )
    {
        printf("Server close connection.\n");
        return -1;
    }
    
    printf("len of date = %d", len);
    printf("time : %s", buff);
    
    close(sockfd);
    
    return 0;
}
