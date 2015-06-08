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

    return 1;
}

int ParamRead_outChnMax(char *ip, int *chnMax){
    unsigned char cmdBytes = { 0xf2, 0, 3 };
    return ParamReadint(ip, cmdBytes, 3, chnMax, 1);
}

int dest1_ParamsReadAll(char *ip){
    int isGood = 1, i = 0;
    isGood &= ParamReadByBytesCmd((unsigned char)1, clsGlobal._ucDb4->ip, 4);
    isGood &= ParamReadByBytesCmd((unsigned char)2, clsGlobal._ucDb4->mac, 6);
    isGood &= ParamReadByIntCmd(ip, (unsigned char)3, &clsGlobal._ucDb4->port, 2);
    isGood &= ParamReadByIntCmd(ip, (unsigned char)4, &clsGlobal._ucDb4->outMode, 1);

    //if (m_supportOutputEnable || m_autoEnableByPrgCnt)
    //{
    isGood &= ParamReadByIntCmd((unsigned char)5, &clsGlobal._ucDb4->outputEnable, 1);
   // }
    if (1)//m_supportPrgMuxInfo
    {
        if (clsGlobal._ucDb4->prgList == NULL){
            clsGlobal._ucDb4->prgList = malloc(sizeof(list_t));
            list_init(clsGlobal._ucDb4->prgList);
        }
        freeUcIpDestPrg(clsGlobal._ucDb4->prgList);

        if (0)//m_supportMultiMux
        {
//            if (ParamReadByBytesCmd((byte)UcIpDest_cmd.prgMuxInfoMultiChnId, muxInfoBytes, 1))
//                _ucDb.outChn = muxInfoBytes[0];
//            else
//            {
//                _ucDb.outChn = 0;
//                //isGood = false;
//            }
        }
        if (1)//m_supportMultiMux || (m_supportMultiMux && _ucDb.outChn > 0)
        {
            unsigned char muxInfoBytes[4] = {0};
            int muxGetRslt = ParamReadByBytesCmd((unsigned char)6, muxInfoBytes, 4);
            if (muxGetRslt && muxInfoBytes[0] > 0)
            {
                if (muxInfoBytes[0] * 3 + 1 == 4)
                {
                    for (int i = 0; i < muxInfoBytes[0]; i++)
                    {
                        UcIpDestPrgMuxInfoSt_st *muxInfo = malloc(sizeof(UcIpDestPrgMuxInfoSt_st));
                        muxInfo->inChn = muxInfoBytes[i * 3 + 1];
                        muxInfo->prgId = muxInfoBytes[i * 3 + 2] + muxInfoBytes[i * 3 + 3] * 0x100;
                        list_append(clsGlobal._ucDb4->prgList, muxInfo);
                    }
                }
            }
        }
    }
    if (isGood)
    {
        //RefreshPlayBtn();
    }
    else
    {
        //btn_play.Visible = false;
    }
    return isGood;
}

