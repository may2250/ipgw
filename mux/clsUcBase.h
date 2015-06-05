#include "datastructdef.h"

#ifndef _IPGW_CLSUCBASE_GET_H_
#define _IPGW_CLSUCBASE_GET_H_


int ParamReadByBytesCmd(char *ip, int cmdType, unsigned char *outBytes, int needBytesLen);
int ParamReadbyte(char *ip, unsigned char *cmdBytes, int cmdLen, unsigned char *outBuf, int needLen);
int ParamReadByIntCmd(char *ip, int cmdType, int *outInt, int needBytesLen);
int ParamReadint(char *ip, unsigned char *cmdBytes, int cmdLen, int *dbInt, int needLen);
#endif