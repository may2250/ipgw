#include "list.h"
#include "datastructdef.h"

#ifndef _IPGW_UCIPDEST_GET_H_
#define _IPGW_UCIPDEST_GET_H_

int ParamsRead_dvbIptvMode(char *ip, int *outMode);
int ParamsRead_ttl(char *ip, int *outMode);
int ParamRead_outChnMax(char *ip, int *chnMax);
int dest1_ParamsReadAll(char *ip);
void GetDb3(list_t *ucDblist);

#endif