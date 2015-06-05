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
    clsGlobal.ipGwDb = malloc(sizeof(IpGWDbSt_st));
    memset(clsGlobal.ipGwDb, 0 ,sizeof(IpGWDbSt_st));
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
            clsProgram.ipGwDb->devNetFun = 1;
        }else{
            clsProgram.ipGwDb->devNetFun = 0;
        }
    }
}

int IpRead(char *ip){
    int rslt = ParamsReadAll(ip);
    rslt &= ParamsRead_dvbIptvMode(ip, &clsGlobal.ipGwDb->dvbIptvMode);
    if (rslt) return 1;
    rslt &= ParamsRead_ttl(ip, &clsGlobal.ipGwDb->ttl);
    return rslt;
}

int IptvRead(char *ip){
    int rslt = 1;
    int chnMax = 0;
//    if (ucIpDest1.ParamRead_outChnMax(ref chnMax) && chnMax > 0)
//    {
//        if(frmWait != null) frmWait.progressBar1.PerformStep();
//        if (ucIpDestDb == null || ucIpDestDb.Length != chnMax)
//            ucIpDestDb = new UcIpDestDbSt3[chnMax];
//        ucIpDest1.ModuleId = 0;
//        rslt = ucIpDest1.ParamsRead_dvbIptvMode(ref ipGwDb.dvbIptvMode);
//        if (!rslt) return false;
//        rslt &= ucIpDest1.ParamsRead_ttl(ref ipGwDb.ttl);
//        if (!rslt) return false;
//        if(frmWait != null) frmWait.progressBar1.PerformStep();
//        for (int i = 0; i < ucIpDestDb.Length; i++)
//        {
//            ucIpDest1.ModuleId = (byte)(i + 1);
//            rslt &= ucIpDest1.ParamsReadAll();
//            if (!rslt) return false;
//            ucIpDest1.GetDb3(ref ucIpDestDb[i]);
//            if (ucIpDestDb[i].outputEnable == 0)
//            {
//                if (ucIpDestDb[i].prgList != null)
//                    ucIpDestDb[i].prgList.Clear();
//            }
//            if(frmWait != null) frmWait.progressBar1.PerformStep();
//        }
//    }
//    else
//    {
//        ucIpDestDb = null;
//    }
    return rslt;
}