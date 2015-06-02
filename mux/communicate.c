#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int communicate(char *ip, unsigned char * sendbuf, int slen, unsigned char* result, int* rlen)
{

    int sockfd,numbytes;
    unsigned char buf[256];
    struct sockaddr_in their_addr;
    int i = 0;
    
    
    ////½¨Á¢Ò»¸öTCPÌ×½Ó¿Ú
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("socket");
        printf("create socket error.½¨Á¢Ò»¸öTCPÌ×½Ó¿ÚÊ§°Ü");
        exit(1);
    }
    
    ////³õÊ¼»¯½á¹¹Ìå£¬Á¬½Óµ½·þÎñÆ÷µÄ2323¶Ë¿Ú
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(161);
    //// their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    /* inet_aton: Convert Internet host address from numbers-and-dots notation in CP
   into binary data and store the result in the structure INP.  */
    if(inet_pton(AF_INET, ip, &their_addr.sin_addr) <= 0)
    {
        printf("[%s] is not a valid IPaddress\n", ip);
        exit(1);
    }
    //inet_aton( "192.168.114.171", &their_addr.sin_addr );
    bzero(&(their_addr.sin_zero),8);
    
    ////ºÍ·þÎñÆ÷½¨Á¢Á¬½Ó
    if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr))==-1)
    {
        perror("connect");
        exit(1);
    }
    
    ////Ïò·þÎñÆ÷·¢ËÍÊý¾Ý, 6¸ö×Ö½ÚÒâÎ¶×ÅÖ»ÓÐhello!±»·¢ËÍ
    if(send(sockfd,sendbuf,slen,0)==-1)
    {
        perror("send");
        exit(1);
    }
    
    ////½ÓÊÜ´Ó·þÎñÆ÷·µ»ØµÄÐÅÏ¢
    memset(buf,0,sizeof(buf));
    if((numbytes = recv(sockfd,buf,256,0))==-1)
    {
        perror("recv");
        exit(1);
    }
    
    //printf("\n####Recive from server bytes nums=[%d]\n",numbytes );

    if(numbytes == 0){
        *rlen = 0;
    }
    else if(numbytes > 0){
        if(numbytes >= slen){
            
            *rlen = numbytes ;        
            memcpy(result, buf, numbytes);    
        }
            
    }else{
        *rlen = -1;
    }
 
    ////¹Ø±Õsocket
    close(sockfd);
}

