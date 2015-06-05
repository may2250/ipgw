
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "communicate.h"
#include "devinfo.h"


//获取设备类型码
int getDeviceType(char *ip,  unsigned int  *outType)
{
	// 双字节，从低到高分别为：PAT\SDT\CAT\NIT	
	
	unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x01;
    sendbuf[3]=0x01;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 4, buf, &slen);
    
    //printf("\n####Recive getDeviceType receive nums=[%d]\n", slen );
    if( 8 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive getDeviceType buf[%d]=0x[%02x]\n",i, buf[i]);    
              
        *outType = (buf[7]<<24| buf[6]<<16|buf[5]<<8| buf[4]) ;  
         res = 0;

    }else 
    	res = -1;

	return res;
	
}


//获取硬件版本号仅显示前两位
int getHardVersion(char *ip,  unsigned int  *outHardVer)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x01;
    sendbuf[3]=0x02;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 4, buf, &slen);
    
    //printf("\n####Recive getHardVersion receive nums=[%d]\n", slen );
    if( 7 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive getHardVersion buf[%d]=0x[%02x]\n",i, buf[i]);    
              
        *outHardVer = (buf[6]<<16| buf[5]<<8|buf[4]) & 0xffffff;  
         res = 0;

    }else 
        res = -1;

    return res;
    
}

//获取软件版本号仅显示前两位
int getSoftVersion(char *ip,  unsigned int  *outSoftVer)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x01;
    sendbuf[3]=0x03;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 4, buf, &slen);
    
    //printf("\n####Recive getSoftVersion receive nums=[%d]\n", slen );
    if( 7 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive getSoftVersion buf[%d]=0x[%02x]\n",i, buf[i]);    
              
        *outSoftVer = (buf[6]<<16| buf[5]<<8|buf[4]) & 0xffffff ;  
         res = 0;

    }else 
        res = -1;

    return res;
    
}

//获取FPGA版本号仅显示前两位
int getFpgaVersion(char *ip,  unsigned int  *outFPGAVer)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x01;
    sendbuf[3]=0x04;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 4, buf, &slen);
    
    //printf("\n####Recive getFpgaVersion receive nums=[%d]\n", slen );
    if( 7 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive getFpgaVersion buf[%d]=0x[%02x]\n",i, buf[i]);    
              
        *outFPGAVer = (buf[6]<<16| buf[5]<<8|buf[4]) & 0xffffff ;  
         res = 0;

    }else 
        res = -1;

    return res;
    
}

void rebootDevice(char *ip)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x01;
    sendbuf[3]=0xf1;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 4, buf, &slen);
    
    //printf("\n#### reboot Device\n");
    
    
}

void restoreFactory(char *ip)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x01;
    sendbuf[3]=0xf2;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 4, buf, &slen);
    
    //printf("\n#### refactory Device\n");
    
    
}

//网络命令字

//获取IP
int getIp(char *ip,  unsigned int  *outIP)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x02;
    sendbuf[3]=0x01;
    sendbuf[4]=0x01;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 5, buf, &slen);
    
    //printf("\n####Recive getIp receive nums=[%d]\n", slen );
    if( 9 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive getIp buf[%d]=0x[%02x]\n",i, buf[i]);    
              
        *outIP = buf[5]<<24 | buf[6]<<16 | buf[7]<<8 | buf[8];  
         res = 0;

    }else 
        res = -1;

    return res;
    
}

//设置ip地址
int setIp(char *ip,  unsigned int devip)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;


    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x02;
    sendbuf[3]=0x01;
    sendbuf[4]=0x02;
    sendbuf[5]=(devip & 0xff000000) >> 24;
    sendbuf[6]=(devip & 0xff0000) >> 16;
    sendbuf[7]=(devip & 0xff00) >> 8;
    sendbuf[8]=(devip & 0xff) ;
    printf("\n####Recive setIp receive ip=[%d.%d.%d.%d]\n", sendbuf[5], sendbuf[6],sendbuf[7],sendbuf[8] );
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 9, buf, &slen);
    
    printf("\n####Recive setIp receive nums=[%d]\n", slen );
    if( 9 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive setIp buf[%d]=0x[%02x]\n",i, buf[i]);    
               
         res = 0;

    }else 
        res = -1;

    return res;
    
}

//获取setSubMask
int getSubMask(char *ip,  unsigned int  *getSubMask)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x02;
    sendbuf[3]=0x02;
    sendbuf[4]=0x01;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 5, buf, &slen);
    
    //printf("\n####Recive getSubMask receive nums=[%d]\n", slen );
    if( 9 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive getSubMask buf[%d]=0x[%02x]\n",i, buf[i]);    
              
        *getSubMask = buf[5]<<24 | buf[6]<<16 | buf[7]<<8 | buf[8];  
         res = 0;

    }else 
        res = -1;

    return res;
    
}

//设置setSubMask地址
int setSubMask(char *ip,  unsigned int  inSubMask)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;


    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x02;
    sendbuf[3]=0x02;
    sendbuf[4]=0x02;
    sendbuf[5]=(inSubMask & 0xff000000) >> 24;
    sendbuf[6]=(inSubMask & 0xff0000) >> 16;
    sendbuf[7]=(inSubMask & 0xff00) >> 8;
    sendbuf[8]=(inSubMask & 0xff) ;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 9, buf, &slen);
    
    // printf("\n####Recive setSubMask receive nums=[%d]\n", slen );
    if( 9 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive setSubMask buf[%d]=0x[%02x]\n",i, buf[i]);    
               
         res = 0;

    }else 
        res = -1;

    return res;
    
}


//获取IP
int getGateway(char *ip,  unsigned int  *outGateway)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x02;
    sendbuf[3]=0x03;
    sendbuf[4]=0x01;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 5, buf, &slen);
    
    //printf("\n####Recive getGateway receive nums=[%d]\n", slen );
    if( 9 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive getGateway buf[%d]=0x[%02x]\n",i, buf[i]);    
              
        *outGateway = buf[5]<<24 | buf[6]<<16 | buf[7]<<8 | buf[8];  
         res = 0;

    }else 
        res = -1;

    return res;
    
}

//设置Gateway地址
int setGateway(char *ip,  unsigned int  inGateway)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;


    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x02;
    sendbuf[3]=0x03;
    sendbuf[4]=0x02;
    sendbuf[5]=(inGateway & 0xff000000) >> 24;
    sendbuf[6]=(inGateway & 0xff0000) >> 16;
    sendbuf[7]=(inGateway & 0xff00) >> 8;
    sendbuf[8]=(inGateway & 0xff) ;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 9, buf, &slen);
    
    // printf("\n####Recive setGateway receive nums=[%d]\n", slen );
    if( 9 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive setGateway buf[%d]=0x[%02x]\n",i, buf[i]);    
               
         res = 0;

    }else 
        res = -1;

    return res;
    
}



//获取Mac
int getMac(char *ip,  unsigned char  *outMac, unsigned int outlen)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x02;
    sendbuf[3]=0x04;
    sendbuf[4]=0x01;
    
    if(outlen!=6){
        printf("outlen !=6\n");
        return -1;
    }

    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 5, buf, &slen);
    
    //printf("\n####Recive getMac receive nums=[%d]\n", slen );
    if( 11 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive getMac buf[%d]=0x[%02x]\n",i, buf[i]);    
                      
         *outMac = buf[5];
         *(outMac+1) = buf[6];
         *(outMac+2) = buf[7];
         *(outMac+3) = buf[8];
         *(outMac+4) = buf[9];
         *(outMac+5) = buf[10];

         res = 0;

    }else 
        res = -1;

    return res;
    
}


//设置Mac地址
int setMac(char *ip,  unsigned char  *outMac)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;


    if(NULL == outMac){
        printf("outMac == NUll\n");
        return -1;
    }

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x02;
    sendbuf[3]=0x04;
    sendbuf[4]=0x02;
    sendbuf[5]=(unsigned char) *outMac ;
    sendbuf[6]=(unsigned char) *(outMac+1);
    sendbuf[7]=(unsigned char) *(outMac+2);
    sendbuf[8]=(unsigned char) *(outMac+3);
    sendbuf[9]=(unsigned char) *(outMac+4);
    sendbuf[10]=(unsigned char) *(outMac+5);
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 11, buf, &slen);
    
    printf("\n####Recive setMac receive nums=[%d]\n", slen );
    if( 11 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive setMac buf[%d]=0x[%02x]\n",i, buf[i]);    
                      
         res = 0;

    }else 
        res = -1;

    return res;
    
}

//获取port
int getPort(char *ip,  unsigned int  *outPort)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x02;
    sendbuf[3]=0x05;
    sendbuf[4]=0x01;
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 5, buf, &slen);
    
    //printf("\n####Recive getPort receive nums=[%d]\n", slen );
    if( 7 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive getPort buf[%d]=0x[%02x]\n",i, buf[i]);    
              
        *outPort = (buf[6]<<8| buf[5]) & 0xffff;  
         res = 0;

    }else 
        res = -1;

    return res;
    
}

//设置pot地址
int setPort(char *ip,  unsigned int  port)
{
    unsigned char buf[10];
    int i = 0;
    unsigned char sendbuf[10];
    int slen=0;
  
    //get call channal signal status
    int  res;


    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x02;
    sendbuf[3]=0x05;
    sendbuf[4]=0x02;
    sendbuf[5]=(unsigned char) (port & 0xff);
    sendbuf[6]=(unsigned char) (port & 0xff00) >> 8;
    
    
    
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 7, buf, &slen);
    
    // printf("\n####Recive setPort receive nums=[%d]\n", slen );
    if( 9 == slen ){
          // for(i=0;i<slen;i++)
          //   printf("Recive setPort buf[%d]=0x[%02x]\n",i, buf[i]);    
               
         res = 0;

    }else 
        res = -1;

    return res;
    
}