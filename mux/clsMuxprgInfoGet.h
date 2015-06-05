
#include "list.h"

#ifndef _CLSMUX_PRGINFO_GET_H_
#define _CLSMUX_PRGINFO_GET_H_

int LittleFormat_fromBytes(int offset, int length, char *inBytes);

int CheckReturnBytes(char *cmdHeadBytes, int headLen, char *rtnBytes, int rtnBytesLen);
int GetSearchingStatus(char *ip, int inChn);
int Search(char *ip, int inChn);
int getPrgCnt(char *ip, int inChn,  int * result);
int getPrograms(char *ip, int inChn, list_t *prginfolist);
int getPrgramInfo(char *ip, int inChn, int prgNo, unsigned char * result, int * reslen);

#endif