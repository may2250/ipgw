#include "datastructdef.h"

#ifndef _IPGW_IPGW_GET_H_
#define _IPGW_IPGW_GET_H_

void Init();
void RefreshIpInOutMode(char *ip);
int IpRead(char *ip);
int RefreshOutPrgCnt();
void DeleteInvalidOutputChn();

#endif
