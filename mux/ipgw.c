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