#include "list.h"
#include "datastructdef.h"

#ifndef _IPGW_UCIPIN_GET_H_
#define _IPGW_UCIPIN_GET_H_


int in_ParamsReadAll(char *ip, int flag);
int ipin_ReadInputStatus(char *ip, int *ipMode, int *lockStatu, int *bitrate, int *_bufUsed);



#endif