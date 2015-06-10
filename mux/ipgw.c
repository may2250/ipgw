#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "communicate.h"
#include "ucIpSrc.h"

ClsProgram_st clsProgram;
ClsGlobal_st  clsGlobal;

void Init(){
    clsGlobal._moduleBaseCmd = 0xf1;
    clsGlobal._moduleId = 0;
    clsGlobal._ucDb = malloc(sizeof(UcIpSrcDbSt_st));
    memset(clsGlobal._ucDb, 0 ,sizeof(UcIpSrcDbSt_st));
    clsGlobal._ucDb4 = malloc(sizeof(UcIpDestDbSt4_st));
    memset(clsGlobal._ucDb4, 0 ,sizeof(UcIpDestDbSt4_st));
    clsGlobal._ucDb4->prgList = malloc(sizeof(list_t));

    clsGlobal.ipGwDb = malloc(sizeof(IpGWDbSt_st));
    memset(clsGlobal.ipGwDb, 0 ,sizeof(IpGWDbSt_st));
    clsGlobal.ucIpDestDb = malloc(sizeof(list_t));
    list_init(clsGlobal.ucIpDestDb);
}

void RefreshIpInOutMode(char *ip)
{
    unsigned char buf[32] = {0};
    unsigned char sendbuf[6] ={0x77,0x6c,0xf0,0x0, 0x1, 0x1};
    int slen=0, i = 0;
    communicate(ip, sendbuf, 5, buf, &slen);

    if(slen == sizeof(sendbuf) + 1){
        int mode = buf[6];
        if(mode == 1){
            clsGlobal.ipGwDb->devNetFun = 1;
        }else{
            clsGlobal.ipGwDb->devNetFun = 0;
        }
    }
}

int IpRead(char *ip){
    int rslt = ParamsReadAll(ip);
    rslt &= ParamsRead_dvbIptvMode(ip, &clsGlobal.ipGwDb->dvbIptvMode);
    if (!rslt) return 0;
    rslt &= ParamsRead_ttl(ip, &clsGlobal.ipGwDb->ttl);
    return rslt;
}

int IptvRead(char *ip){
    int rslt = 1, i = 0;
    int chnMax = 0;
    if (ParamRead_outChnMax(ip, &chnMax) && chnMax > 0){
        clsGlobal._moduleId = 0;
        rslt = ParamsRead_dvbIptvMode(ip, &clsGlobal.ipGwDb->dvbIptvMode);
        if (!rslt) return 0;
        rslt &= ParamsRead_ttl(ip, &clsGlobal.ipGwDb->ttl);
        if (!rslt) return 0;
        //clear db3
        freeUcIpDestdbs(clsGlobal.ucIpDestDb);
        printf("==chnMax==%d\n", chnMax);
        for (i = 0; i < chnMax; i++)
        {
            clsGlobal._moduleId = (i + 1);
            rslt &= dest1_ParamsReadAll(ip);
            if (!rslt) return 0;
            GetDb3(clsGlobal.ucIpDestDb);
        }
   }
   return rslt;
}

int RefreshOutPrgCnt(){
    int outPrgCnt = 0, i = 0;
    ChannelProgramSt *pst = NULL;
    if(clsGlobal.ipGwDb->dvbIptvMode == 0)// 0=mpts, 1=spts
    {
        list_get(&(clsProgram.inPrgList), 0, &pst);
        if(pst != NULL){
            outPrgCnt = list_len(&pst->prgNodes);
            return outPrgCnt;
        }
    }
    else
    {
        UcIpDestDbSt3_st *db3 = NULL;
        if(list_len(clsGlobal.ucIpDestDb)>0){
            for(i=0;i<list_len(clsGlobal.ucIpDestDb);i++){
                list_get(clsGlobal.ucIpDestDb, i, &db3);
                if(db3->prgList != NULL){
                    outPrgCnt += list_len(db3->prgList);
                }
            }
        }
        return outPrgCnt;
    }
}

void DeleteInvalidOutputChn(){
    int i = 0, j = 0, k = 0, m = 0;
    ChannelProgramSt *pst = NULL;
    Dev_prgInfo_st *inprg = NULL;
    for(i=0;i<list_len(clsGlobal.ucIpDestDb);i++){
        UcIpDestDbSt3_st *eachChn = NULL;
        list_get(clsGlobal.ucIpDestDb, i, &eachChn);
        if(eachChn->prgList != NULL){
            UcIpDestPrgMuxInfoSt_st *prg = NULL;
            for(j=0;j<list_len(eachChn->prgList);){
                list_get(eachChn->prgList, j, &prg);
                if(&clsProgram.inPrgList == NULL || list_len(&clsProgram.inPrgList) <= 0){
                    freeUcIpDestPrg(eachChn->prgList);
                    break;
                }
                int isInValidPrg = 1;
                for(k=0;k<list_len(&clsProgram.inPrgList);k++){
                    list_get(&clsProgram.inPrgList, k, &pst);
                    if(pst->channelId == prg->inChn){
                        if(&pst->prgNodes != NULL){
                            for(m=0;m<list_len(&pst->prgNodes);m++){
                                list_get(&pst->prgNodes, m, &inprg);
                                if(inprg->prgNum == prg->prgId)                                {
                                    isInValidPrg = 0;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                if(isInValidPrg){
                    printf("===DeleteInvalidOutputChn===del\n");
                    list_pop(eachChn->prgList, j);
                }else{
                    j++;
                }
            }
        }

    }
}

