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

    clsGlobal._inDb = malloc(sizeof(UcIpInDbSt_st));
    memset(clsGlobal.ipGwDb, 0 ,sizeof(UcIpInDbSt_st));

}

void RefreshIpInOutMode(char *ip){
    unsigned char buf[32] = {0};
    unsigned char sendbuf[6] ={0x77,0x6c,0xf0,0x0, 0x1, 0x1};
    int slen=0, i = 0;
    communicate(ip, sendbuf, 6, buf, &slen);

    if(slen == sizeof(sendbuf) + 1){
        int mode = buf[6];
        if(mode == 1){
            clsGlobal.ipGwDb->devNetFun = 1;
        }else{
            clsGlobal.ipGwDb->devNetFun = 0;
        }
    }
}

void NetApply(char *ip){
    unsigned char buf[32] = {0};
    unsigned char sendbuf[7] ={0x77, 0x6c, 0xf0, 0x0, 0x1, 0x2, (unsigned char)clsGlobal.ipGwDb->devNetFun};
    int slen=0, i = 0;
    communicate(ip, sendbuf, 7, buf, &slen);

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
                    free(eachChn->prgList);
                    eachChn->prgList = NULL;
                    break;
                }
                int isInValidPrg = 1;
                for(k=0;k<list_len(&clsProgram.inPrgList);k++){
                    list_get(&clsProgram.inPrgList, k, &pst);
                    if(pst->channelId == prg->inChn){
                        if(&pst->prgNodes != NULL){
                            for(m=0;m<list_len(&pst->prgNodes);m++){
                                list_get(&pst->prgNodes, m, &inprg);
                                if(inprg->prgNum == prg->prgId) {
                                    isInValidPrg = 0;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                if(isInValidPrg){
                    list_pop(eachChn->prgList, j);
                    printf("===DeleteInvalidOutputChn===del\n");
                }else{
                    j++;
                }
            }
        }

    }
}

void EnableValidOutChn(){
    int i = 0;
    if (clsGlobal.ucIpDestDb != NULL)
    {
        UcIpDestDbSt3_st *db3 = NULL;
        if (clsGlobal.ipGwDb->dvbIptvMode == 0)
        {
            list_get(clsGlobal.ucIpDestDb, 0, &db3);
            db3->outputEnable = 1;
        }else{
            for (i = 0; i < list_len(clsGlobal.ucIpDestDb); i++)
            {
                list_get(clsGlobal.ucIpDestDb, i, &db3);
                if (db3->prgList == NULL )
                {
                    db3->outputEnable = 0;
                }
                else
                {
                    if(list_len(db3->prgList) == 0){
                        db3->outputEnable = 0;
                    }else{
                        db3->outputEnable = 1;
                    }
                }
            }
        }
    }
}

void OutChnPrg_output(int inChn, int prgId, int outChnId){
    //OutChnPrg_delete
    if (clsGlobal.ucIpDestDb == NULL)
        return;
    int i = 0, j = 0;
    UcIpDestDbSt3_st *db3 = NULL;
    for(i = 0; i < list_len(clsGlobal.ucIpDestDb); i++)
    {
        list_get(clsGlobal.ucIpDestDb, i, &db3);
        if (db3->prgList != NULL)
        {
            UcIpDestPrgMuxInfoSt_st * muxinfo = NULL;
            for(j=0;j<list_len(db3->prgList); j++){
                list_get(db3->prgList, j, &muxinfo);
                if(muxinfo->inChn == inChn && muxinfo->prgId == prgId){
                    freeUcIpDestPrg(db3->prgList);
                    free(db3->prgList);
                    db3->prgList = NULL;
                    break;
                }
            }
        }
    }
    if(list_len(clsGlobal.ucIpDestDb)< outChnId || outChnId < 1)
        return;
    outChnId--;
    list_get(clsGlobal.ucIpDestDb, outChnId, &db3);
    if (db3->prgList != NULL){
        freeUcIpDestPrg(db3->prgList);
        free(db3->prgList);
        db3->prgList = NULL;
    }
    db3->prgList = malloc(sizeof(list_t));
    list_init(db3->prgList);
    UcIpDestPrgMuxInfoSt_st *newOutPrg = malloc(sizeof(UcIpDestPrgMuxInfoSt_st));
    newOutPrg->inChn = inChn;
    newOutPrg->prgId = prgId;
    newOutPrg->avPidListLen = 0;
    list_append(db3->prgList, newOutPrg);
}

int CheckSameDest(){
    int i = 0, j = 0, k = 0;
    UcIpDestDbSt3_st *db3 = NULL;
    UcIpDestDbSt3_st *dbj3 = NULL;
    for(i = 1; i < list_len(clsGlobal.ucIpDestDb); i++){
        list_get(clsGlobal.ucIpDestDb, i, &db3);
        if (db3->outputEnable != 1)
            continue;
        for (j = 0; j < i; j++)
        {
            list_get(clsGlobal.ucIpDestDb, j, &dbj3);
            if (dbj3->outputEnable != 1)
                continue;
            if(db3->port == dbj3->port)
            {
                int isSame = 1;
                for(k = 0; k < 4; k++)
                {
                    if(db3->ip[k] != dbj3->ip[k])
                    {
                        isSame = 0;
                        break;
                    }
                }
                for(k = 0; k < 6; k++)
                {
                    if(db3->mac[k] != dbj3->mac[k])
                    {
                        isSame = 0;
                        break;
                    }
                }
                if(isSame)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int IpWrite(char *ip){
    clsGlobal._moduleId = 1;
    //int rslt = ucIpSrc1.ParamsWriteAll();
    int rslt = ParamsWrite_dvbIptvMode(ip, clsGlobal.ipGwDb->dvbIptvMode);
    if (!rslt) return 0;
    rslt &= ParamsWrite_ttl(ip, clsGlobal.ipGwDb->ttl);
    if (!rslt) return 0;
    return rslt;
}

int IptvWrite(char *ip){
    int rslt = 0, i = 0;
    clsGlobal._moduleId = 0;
    rslt = ParamsRead_dvbIptvMode(ip, &clsGlobal.ipGwDb->dvbIptvMode);
    rslt &= ParamsRead_ttl(ip, &clsGlobal.ipGwDb->ttl);
    UcIpDestDbSt3_st *db3 = NULL;
    for (i = 0; i < list_len(clsGlobal.ucIpDestDb); i++)
    {
        clsGlobal._moduleId = (unsigned char)(i + 1);
        SetDb3(i);
        list_get(clsGlobal.ucIpDestDb, i, &db3);
        if (clsGlobal.ipGwDb->dvbIptvMode == 0)
        {
            if (db3->outputEnable == 0) // 如果未启用，则只发送“enable、apply”命令
                rslt &= ParamsWriteAll(ip, 0x20);
            else
                rslt &= ParamsWriteAll(ip, 0xbf);
            break;
        }
        else
        {
            if (db3->outputEnable == 0){    // 如果未启用，则只发送“enable、apply”命令
                rslt &= ParamsWriteAll(ip, 0x20);
            }else{
                rslt &= ParamsWriteAll(ip, 0xff);
            }
        }
    }
    return rslt;
}

