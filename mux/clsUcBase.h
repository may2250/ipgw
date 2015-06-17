#include "datastructdef.h"

#ifndef _IPGW_CLSUCBASE_GET_H_
#define _IPGW_CLSUCBASE_GET_H_


int ParamReadByBytesCmd(char *ip, int cmdType, unsigned char *outBytes, int needBytesLen);
int ParamReadbyte(char *ip, unsigned char *cmdBytes, int cmdLen, unsigned char *outBuf, int needLen);
int ParamReadByIntCmd(char *ip, int cmdType, int *outInt, int needBytesLen);
int ParamReadint(char *ip, unsigned char *cmdBytes, int cmdLen, int *dbInt, int needLen);
int ParamWriteByBytesCmd(char *ip, int cmdType, unsigned char *writeBytes, int writeBytesLen);
int ParamWriteByIntCmd(char *ip, int cmdType, int writeBytes, int writeBytesLen);
int ParamWriteInt(char *ip, unsigned char *cmdBytes, int cmdLen, int writeInt, int writeLen);
int ParamWriteByte(char *ip, unsigned char *cmdBytes, int cmdLen, unsigned char *writeBytes, int writeLen);
int ipin_ParamReadByBytesCmd(char *ip, unsigned char cmdType, unsigned char cmdSubType, unsigned char *outBytes, int needBytesLen);
int ipin_ParamReadByIntCmd(char *ip, unsigned char cmdType, unsigned char cmdSubType, int *outInt, int needBytesLen);


#endif
