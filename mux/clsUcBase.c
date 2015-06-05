#include <stdio.h>
#include <stdlib.h>
#include "clsUcBase.h"

extern ClsGlobal_st  clsGlobal;

int ParamReadbyte(char *ip, unsigned char *cmdBytes, int cmdLen, unsigned char *outBuf, int needLen){
    if (cmdBytes == NULL)
        return 1;
    unsigned char buf[1024] = {0};
    unsigned char sendbuf[32] = {0};
    int iAddr = 0;
    int rlen = 0;
    sendbuf[iAddr++] = 0x77;
    sendbuf[iAddr++] = 0x6c;
    memcpy(sendbuf+iAddr, cmdBytes, cmdLen);
    iAddr += cmdLen;
    sendbuf[iAddr++] = 1; // read

    communicate(ip, sendbuf, iAddr, buf, &rlen);
    if (needLen == -1)
    {
        if (rlen > iAddr)
        {
            printf("ParamReadbyte::::assert\n");
            //outBuf = new byte[rlen - iAddr];
            //Array.Copy(buf, iAddr, outBuf, 0, outBuf.Length);
        }
    }
    else
    {
        //outBuf = new byte[needLen];
        if (rlen < iAddr + needLen)
            return 1;

        memcpy(outBuf, buf+iAddr, needLen);

    }
    return 0;
}

int ParamReadint(char *ip, unsigned char *cmdBytes, int cmdLen, int *dbInt, int needLen){
    if (cmdBytes == NULL)
        return 1;
    unsigned char buf[1024] = {0};
    unsigned char sendbuf[32] = {0};
    unsigned char outBuf[needLen];
    int iAddr = 0;
    int rlen = 0;
    sendbuf[iAddr++] = 0x77;
    sendbuf[iAddr++] = 0x6c;
    memcpy(sendbuf+iAddr, cmdBytes, cmdLen);
    iAddr += cmdLen;
    sendbuf[iAddr++] = 1; // read

    communicate(ip, sendbuf, iAddr, buf, &rlen);
    if (needLen == -1)
    {
        if (rlen > iAddr)
        {
            printf("ParamReadbyte::::assert\n");
            //outBuf = new byte[rlen - iAddr];
            //Array.Copy(buf, iAddr, outBuf, 0, outBuf.Length);
        }
    }
    else
    {
        if (rlen < iAddr + needLen)
            return 1;
        memcpy(outBuf, buf+iAddr, needLen);
        int i = 0;
        for(i=0;i<needLen;i++){
            printf("===outBuf==[%x]\n", outBuf[i]);
        }
        *dbInt = LittleFormat_fromBytes(0, needLen, outBuf);
        if(needLen == 1){
            *dbInt = *dbInt & 0x000000ff;
        }else if(needLen == 2){
            *dbInt = *dbInt & 0x0000ffff;
        }else if(needLen == 3){
            *dbInt = *dbInt & 0x00ffffff;
        }else{
            *dbInt = *dbInt;
        }

        printf("===dbInt==%x\n", *dbInt);
    }
    return 0;
}


int ParamReadByBytesCmd(char *ip, int cmdType, unsigned char *outBytes, int needBytesLen)
{
    unsigned char cmdBytes[3] = { clsGlobal._moduleBaseCmd, clsGlobal._moduleId, (unsigned char)cmdType };
    return ParamReadbyte(ip, cmdBytes, 3, outBytes, needBytesLen);
}

int ParamReadByIntCmd(char *ip, int cmdType, int *outInt, int needBytesLen)
{
    unsigned char cmdBytes[3] = { clsGlobal._moduleBaseCmd, clsGlobal._moduleId, (unsigned char)cmdType };
    return ParamReadint(ip, cmdBytes, 3, outInt, needBytesLen);
}

