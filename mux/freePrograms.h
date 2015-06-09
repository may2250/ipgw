#include "datastructdef.h"
#include "list.h"



#ifndef _FREE_PROGRAMS_H_
#define _FREE_PROGRAMS_H_


int freePrograms(list_t *prginfolist);
int freeProgramsMalloc(Dev_prgInfo_st * data);
int freeUcIpDestPrg(list_t *prginfolist);
int freeUcIpDestdbs(list_t *prginfolist);

#endif
