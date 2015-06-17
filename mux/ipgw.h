#include "datastructdef.h"

#ifndef _IPGW_IPGW_GET_H_
#define _IPGW_IPGW_GET_H_

void Init();
void RefreshIpInOutMode(char *ip);
void NetApply(char *ip);
int IpRead(char *ip);
int RefreshOutPrgCnt();
void DeleteInvalidOutputChn();
void EnableValidOutChn();
void OutChnPrg_output(int inChn, int prgId, int outChnId);
int CheckSameDest();
int IptvWrite(char *ip);
int IpWrite(char *ip);

#endif
