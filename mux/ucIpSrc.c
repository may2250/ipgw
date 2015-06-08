#include <stdio.h>
#include <stdlib.h>
#include "ucIpSrc.h"
#include "clsUcBase.h"

extern ClsGlobal_st  clsGlobal;

int ParamsReadAll(char *ip){
    int isGood = 1;
    clsGlobal._moduleId = 1;
    isGood &= ParamReadByBytesCmd(ip, 1, clsGlobal._ucDb->ip, 4);
    //printf("===ip==%d.%d.%d.%d\n", clsGlobal._ucDb->ip[0], clsGlobal._ucDb->ip[1],clsGlobal._ucDb->ip[2],clsGlobal._ucDb->ip[3]);
    isGood &= ParamReadByBytesCmd(ip, 2, clsGlobal._ucDb->mac, 6);
    isGood &= ParamReadByIntCmd(ip, 3, &clsGlobal._ucDb->port, 2);
    if (1)
    {
        isGood &= ParamReadByIntCmd(ip, 4, &clsGlobal._ucDb->netInterfaceMode, 1);
    }
    else
    {
        clsGlobal._ucDb->netInterfaceMode = 1;
    }
//    if (lockStatusBitrateEnable)
//    {
//        ReadInputStatus(out _lockStatus, out _inputBt);
//    }
    return isGood;
}

int ParamsRead_dvbIptvMode(char *ip, int *outMode){
    unsigned char cmdBytes[3] = { 0xf2, 0, 1 };
    return ParamReadint(ip, cmdBytes, 3, outMode, 1);
}

int ParamsRead_ttl(char *ip, int *outMode){
    unsigned char cmdBytes[3] = { 0xf2, 0, 2 };
    return ParamReadint(ip, cmdBytes, 3, outMode, 1);
}

int ReadInputStatus(char *ip, int *lockStatus, int *bitrate){
    *lockStatus = *bitrate = 0;
    clsGlobal._moduleId = 2;
    int isGood = ParamReadByIntCmd(ip, 1, lockStatus, 1);
    isGood &= ParamReadByIntCmd(ip, 2, bitrate, 4);
    clsGlobal._moduleId = 1;

    return 0;
}
