#include "list.h"
#include "datastructdef.h"

#ifndef _IPGW_UCIPSRC_GET_H_
#define _IPGW_UCIPSRC_GET_H_


int ParamsReadAll(char *ip);
int ParamsRead_dvbIptvMode(char *ip, int *outMode);
int ParamsRead_ttl(char *ip, int *outMode);
int ReadInputStatus(char *ip, int *lockStatus, int *bitrate);

#endif
