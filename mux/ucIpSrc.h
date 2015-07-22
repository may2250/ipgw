#include "list.h"
#include "datastructdef.h"

#ifndef _IPGW_UCIPSRC_GET_H_
#define _IPGW_UCIPSRC_GET_H_


int ParamsReadAll(char *ip);

int ReadInputStatus(char *ip, int *lockStatus, int *bitrate);

int SrcParamsWriteAll(char *ip);

#endif
