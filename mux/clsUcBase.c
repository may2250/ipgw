#include <stdio.h>
#include <stdlib.h>
#include "clsUcBase.h"

extern ClsGlobal_st  clsGlobal;

int ParamReadbyte(char *ip, unsigned char *cmdBytes, int cmdLen, unsigned char *outBuf, int needLen){
    if (cmdBytes == NULL)
        return 0;
    unsigned char buf[1024] = {0};
    unsigned char sendbuf[32] = {0};
    int iAddr = 0;
    int rlen = 0;
    sendbuf[iAddr++] = 0x77;
    sendbuf[iAddr++] = 0x6c;
    memcpy(sendbuf+iAddr, cmdBytes, cmdLen);
    iAddr += cmdLen;
    sendbuf[iAddr++] = 1; // read

//    int i = 0;
//    for(i=0;i<8;i++){
//        printf("===sendbuf==[%x]\n", sendbuf[i]);
//    }
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
            return 0;
//        for(i=0;i<rlen;i++){
//            printf("===buf==[%x]\n", buf[i]);
//        }
        memcpy(outBuf, buf+iAddr, needLen);
    }
    return 1;
}

int ParamReadint(char *ip, unsigned char *cmdBytes, int cmdLen, int *dbInt, int needLen){
    int i = 0;
    if (cmdBytes == NULL)
        return 0;
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
//    for(i=0;i<8;i++){
//        printf("===sendbuf==[%x]\n", sendbuf[i]);
//    }
    communicate(ip, sendbuf, iAddr, buf, &rlen);
    if (needLen == -1)
    {
        if (rlen > iAddr)
        {
            printf("ParamReadint::::assert\n");
            //outBuf = new byte[rlen - iAddr];
            //Array.Copy(buf, iAddr, outBuf, 0, outBuf.Length);
        }
    }
    else
    {
        if (rlen < iAddr + needLen)
            return 0;
        memcpy(outBuf, buf+iAddr, needLen);
//        printf("========================\n");
//        for(i=0;i<needLen;i++){
//            printf("===outBuf==[%x]\n", outBuf[i]);
//        }

        int offset = 0;
        *dbInt = 0;
        for (i = 0; i < needLen; i++)
        {
            *dbInt += (outBuf[offset++] << (i * 8));
        }
     //   printf("===dbInt==%d\n", *dbInt);
    }
    return 1;
}

int ParamWriteByte(char *ip, unsigned char *cmdBytes, int cmdLen, unsigned char *writeBytes, int writeLen)
{
    if (cmdBytes == NULL)
        return 0;
    unsigned char buf[1024] = {0};
    unsigned char sendbuf[256] = {0};
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
//    printf("======================\n");
//    for(i=0;i<12;i++){
//        printf("[%d]%x::", i, sendbuf[i]);
//    }
    communicate(ip, sendbuf, iAddr+writeLen, buf, &rlen);

//    if (rlen != iAddr + 1 || buf[iAddr] != 0)
//    {
//        printf("---=-=-rlen==%d\n", rlen);
//        return 1;
//    }
    return 1;
}

int ParamWriteInt(char *ip, unsigned char *cmdBytes, int cmdLen, int writeInt, int writeLen)
{
    if (cmdBytes == NULL)
        return 0;
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
//    printf("======================\n");
//    for (i = 0; i < 12; i++)
//    {
//        printf("[%d]=%x::", i, sendbuf[i]);
//    }
    communicate(ip, sendbuf, iAddr+writeLen, buf, &rlen);
//    if (rlen != iAddr + 1 || buf[iAddr] != 0)
//    {
//        printf("xxxxxxrlen==%d\n", rlen);
//        return 1;
//    }
    return 1;
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

int ipin_ParamReadByBytesCmd(char *ip, unsigned char cmdType, unsigned char cmdSubType, unsigned char *outBytes, int needBytesLen)
{
    unsigned char cmdBytes[4] = { clsGlobal._moduleBaseCmd, clsGlobal._moduleId, cmdType, cmdSubType };
    return ParamReadbyte(ip, cmdBytes, 4, outBytes, needBytesLen);
}

int ipin_ParamReadByIntCmd(char *ip, unsigned char cmdType, unsigned char cmdSubType, int *outInt, int needBytesLen)
{
    unsigned char cmdBytes[4] = { clsGlobal._moduleBaseCmd, clsGlobal._moduleId, cmdType, cmdSubType };
    return ParamReadint(ip, cmdBytes, 4, outInt, needBytesLen);
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

int ParamWriteByBytesCmd2(char *ip, unsigned char cmdType, unsigned char cmdSubType, unsigned char *writeBytes, int writeBytesLen)
{
    unsigned char cmdBytes[] = { clsGlobal._moduleBaseCmd, clsGlobal._moduleId, cmdType, cmdSubType };
    return ParamWriteByte(ip, cmdBytes, 4, writeBytes, writeBytesLen);
}

int ParamWriteByIntCmd2(char *ip, unsigned char cmdType, unsigned char cmdSubType, int writeInt, int writeBytesLen)
{
    unsigned char cmdBytes[] = { clsGlobal._moduleBaseCmd, clsGlobal._moduleId, cmdType, cmdSubType };
    return ParamWriteInt(ip, cmdBytes, 4, writeInt, writeBytesLen);
}

