#include <stdio.h>
#include <stdlib.h>
#include "ucIpIn.h"
#include "clsUcBase.h"

extern ClsGlobal_st  clsGlobal;

int in_ParamsReadAll(char *ip, int flag){
    unsigned char cmdBytes[5] = { clsGlobal._moduleBaseCmd, clsGlobal._moduleId, 2, 1, 0 };
    int isGood = 1;
    isGood &= ipin_ParamReadByBytesCmd(ip, 1, 1, clsGlobal._inDb->ip, 4);
    isGood &= ipin_ParamReadByBytesCmd(ip, 1, 2, clsGlobal._inDb->mac, 6);

    cmdBytes[4] = 1;
    isGood &= ParamReadint(ip, cmdBytes, 5, &clsGlobal._inDb->valid, 1);
    cmdBytes[4] = 2;
    isGood &= ParamReadbyte(ip, cmdBytes, 5, clsGlobal._inDb->srcIp, 4);
    cmdBytes[4] = 3;
    isGood &= ParamReadint(ip, cmdBytes, 5, &clsGlobal._inDb->port, 2);
    cmdBytes[4] = 5;
    isGood &= ParamReadint(ip, cmdBytes, 5, &clsGlobal._inDb->unicastMulticast, 1);
    cmdBytes[4] = 6;
    isGood &= ParamReadint(ip, cmdBytes, 5, &clsGlobal._inDb->inStreamType, 1);
    if (flag)
    {
        cmdBytes[4] = 7;
        isGood &= ParamReadint(ip, cmdBytes, 5, &clsGlobal._inDb->outStreamBitrate, 4);
    }
    //isGood &= ReadInputStatus(out _ipMode, out _lockStatus, out _inBitrate);
    return isGood;
}

int ipin_ReadInputStatus(char *ip, int *ipMode, int *lockStatu, int *bitrate, int *_bufUsed){
    *lockStatu = *bitrate = *ipMode = *_bufUsed = 0;
    unsigned char rcvBytes[32] = {0};
    int rslt = 1;
    if(1){
        rslt = ipin_ParamReadByIntCmd(ip, 1, 6, ipMode, 1);
        rslt &= ipin_ParamReadByIntCmd(ip, 1, 8, lockStatu, 1);
        rslt &= ipin_ParamReadByBytesCmd(ip, 1, 9, rcvBytes, 5);
        *bitrate = rcvBytes[0] + (rcvBytes[1] << 8) + (rcvBytes[2] << 16) + (rcvBytes[3] << 24);
        *_bufUsed = rcvBytes[4];

    }
    return rslt;
}