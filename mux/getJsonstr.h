#include <string.h>
#include "list.h"
#include "datastructdef.h"
#include "clsMuxprgInfoGet.h"
#include "devinfo.h"
#include "freePrograms.h"
#include "cJSON.h"

#ifndef _IPGW_GETJSONSTR_GET_H_
#define _IPGW_GETJSONSTR_GET_H_

void getPrgsJson(char *ip, char *outprg);
void getbaseJson(char *ip, char *outprg);

#endif
