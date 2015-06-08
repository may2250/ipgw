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
//        int i = 0;
//        for(i=0;i<needLen;i++){
//            printf("===outBuf==[%x]\n", outBuf[i]);
//        }
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

        //printf("===dbInt==%x\n", *dbInt);
    }
    return 0;
}

int ParamWriteByte(char *ip, unsigned char *cmdBytes, int cmdLen, unsigned char *writeBytes, int writeLen)
{
    if (cmdBytes == NULL)
        return 1;
    unsigned char buf[1024] = {0};
    unsigned char sendbuf[32] = {0};
    int iAddr = 0, i = 0;

    sendbuf[iAddr++] = 0x77;
    sendbuf[iAddr++] = 0x6c;
    memcpy(sendbuf+iAddr, cmdBytes, cmdLen);
    iAddr += cmdLen;
    sendbuf[iAddr++] = 2; // write
    int rlen = 0;
    if (writeBytes != NULL && writeLen > 0)
    {
        memcpy(sendbuf+iAddr, writeBytes, writeLen);
    }
//    for(i=0;i<12;i++){
//        printf("[%d]::%x\n", i, sendbuf[i]);
//    }
    communicate(ip, sendbuf, iAddr+writeLen, buf, &rlen);

//    if (rlen != iAddr + 1 || buf[iAddr] != 0)
//    {
//        printf("---=-=-rlen==%d\n", rlen);
//        return 1;
//    }
    return 0;
}

int ParamWriteInt(char *ip, unsigned char *cmdBytes, int cmdLen, int writeInt, int writeLen)
{
    if (cmdBytes == NULL)
        return 1;
    int i = 0, iAddr = 0, rlen = 0, offset = 0;
    char writeBytes[writeLen];
    for (i = 0; i < writeLen; i++)
    {
        writeBytes[offset++] = (unsigned char)(writeInt);
        writeInt >>= 8;
    }
    unsigned char buf[1024] = {0};
    unsigned char sendbuf[32] = {0};

    sendbuf[iAddr++] = 0x77;
    sendbuf[iAddr++] = 0x6c;
    memcpy(sendbuf+iAddr, cmdBytes, cmdLen);
    iAddr += cmdLen;
    sendbuf[iAddr++] = 2; // write
    if (writeBytes != NULL && writeLen > 0)
    {
        memcpy(sendbuf+iAddr, writeBytes, writeLen);
    }

    communicate(ip, sendbuf, iAddr+writeLen, buf, &rlen);
//    if (rlen != iAddr + 1 || buf[iAddr] != 0)
//    {
//        printf("xxxxxxrlen==%d\n", rlen);
//        return 1;
//    }
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

int ParamWriteByBytesCmd(char *ip, int cmdType, unsigned char *writeBytes, int writeBytesLen)
{
   unsigned char cmdBytes[] = { clsGlobal._moduleBaseCmd, clsGlobal._moduleId, (unsigned char)cmdType };
   return ParamWriteByte(ip, cmdBytes, 3, writeBytes, writeBytesLen);
}

int ParamWriteByIntCmd(char *ip, int cmdType, int writeBytes, int writeBytesLen)
{
   unsigned char cmdBytes[] = { clsGlobal._moduleBaseCmd, clsGlobal._moduleId, (unsigned char)cmdType };
   return ParamWriteInt(ip, cmdBytes, 3, writeBytes, writeBytesLen);
}

