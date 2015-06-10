#include <stdio.h>
#include <stdlib.h>
#include "ucIpDest.h"
#include "clsUcBase.h"

extern ClsGlobal_st  clsGlobal;

int ParamsRead_dvbIptvMode(char *ip, int *outMode){
    unsigned char cmdBytes[3] = { 0xf2, 0, 1 };
    return ParamReadint(ip, cmdBytes, 3, outMode, 1);
}

int ParamsRead_ttl(char *ip, int *outMode){
    unsigned char cmdBytes[3] = { 0xf2, 0, 2 };
    return ParamReadint(ip, cmdBytes, 3, outMode, 1);
}

int ParamRead_outChnMax(char *ip, int *chnMax){
    unsigned char cmdBytes[3] = { 0xf2, 0, 3 };
    return ParamReadint(ip, cmdBytes, 3, chnMax, 1);
}

int dest1_ParamsReadAll(char *ip){
    int isGood = 1, i = 0;
    clsGlobal._moduleBaseCmd = 0xf2;
    isGood &= ParamReadByBytesCmd(ip, (unsigned char)1, clsGlobal._ucDb4->ip, 4);
    isGood &= ParamReadByBytesCmd(ip, (unsigned char)2, clsGlobal._ucDb4->mac, 6);
    isGood &= ParamReadByIntCmd(ip, (unsigned char)3, &clsGlobal._ucDb4->port, 2);
    isGood &= ParamReadByIntCmd(ip, (unsigned char)4, &clsGlobal._ucDb4->outMode, 1);
    //if (m_supportOutputEnable || m_autoEnableByPrgCnt)
    //{
    isGood &= ParamReadByIntCmd(ip, (unsigned char)5, &clsGlobal._ucDb4->outputEnable, 1);
   // }
    //printf("--dest1_ParamsReadAll---outputEnable==%d\n", clsGlobal._ucDb4->outputEnable);
    if (1)//m_supportPrgMuxInfo
    {
        freeUcIpDestPrg(clsGlobal._ucDb4->prgList);
        if (clsGlobal._ucDb4->prgList == NULL){
            clsGlobal._ucDb4->prgList = malloc(sizeof(list_t));
            list_init(clsGlobal._ucDb4->prgList);
        }
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
            int muxGetRslt = ParamReadByBytesCmd(ip, (unsigned char)6, muxInfoBytes, 4);
//            for(i=0;i<4;i++){
//                printf("===muxInfoBytes==[%x]\n", muxInfoBytes[i]);
//            }
            if (muxGetRslt && muxInfoBytes[0] > 0)
            {
                if (muxInfoBytes[0] * 3 + 1 == 4)
                {
                    for (i = 0; i < muxInfoBytes[0]; i++)
                    {
                        UcIpDestPrgMuxInfoSt_st *muxInfo = malloc(sizeof(UcIpDestPrgMuxInfoSt_st));
                        memset(muxInfo, 0, sizeof(UcIpDestPrgMuxInfoSt_st));
                        muxInfo->inChn = muxInfoBytes[i * 3 + 1];
                        muxInfo->prgId = muxInfoBytes[i * 3 + 2] + muxInfoBytes[i * 3 + 3] * 0x100;
                        list_append(clsGlobal._ucDb4->prgList, muxInfo);
                    }
                }
            }
        }
    }
//    UcIpDestPrgMuxInfoSt_st *tmpmuxinfo = NULL;
//    for(i=0;i<list_len(clsGlobal._ucDb4->prgList);i++){
//        list_get(clsGlobal._ucDb4->prgList, i, &tmpmuxinfo);
//        printf("===[%d]=prgid=%x\n", i, tmpmuxinfo->prgId);
//    }
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

void GetDb3(list_t *ucDblist)
{
    int i = 0;
    UcIpDestDbSt3_st *ucDb = malloc(sizeof(UcIpDestDbSt3_st));
    memcpy(ucDb->ip, clsGlobal._ucDb4->ip, 4);
    memcpy(ucDb->mac, clsGlobal._ucDb4->mac, 6);
    ucDb->outMode = clsGlobal._ucDb4->outMode;
    ucDb->port = clsGlobal._ucDb4->port;
    ucDb->outputEnable = clsGlobal._ucDb4->outputEnable;
    if(ucDb->outputEnable != 0){
        if(clsGlobal._ucDb4->prgList != NULL){
            if(list_len(clsGlobal._ucDb4->prgList)>0){
                ucDb->prgList = malloc(sizeof(list_t));
                list_init(ucDb->prgList);
                UcIpDestPrgMuxInfoSt_st *eachPrg = NULL;
                UcIpDestPrgMuxInfoSt_st *curPrg = malloc(sizeof(UcIpDestPrgMuxInfoSt_st));
                for(i=0;i<list_len(clsGlobal._ucDb4->prgList);i++){
                    list_get(clsGlobal._ucDb4->prgList, i, &eachPrg);
                    if(eachPrg->avPidListLen>0){
                        curPrg->avPidListLen = eachPrg->avPidListLen;
                        curPrg->avPidList = malloc(eachPrg->avPidListLen);
                        memcpy(curPrg->avPidList, eachPrg->avPidList, eachPrg->avPidListLen);
                    }else{
                        curPrg->avPidListLen = 0;
                    }
                    curPrg->inChn = eachPrg->inChn;
                    curPrg->pmtPID = eachPrg->pmtPID;
                    curPrg->prgId = eachPrg->prgId;
                    list_append(ucDb->prgList, curPrg);
                }
            }
        }
    }else{
        ucDb->prgList = NULL;
    }
    list_append(ucDblist, ucDb);
}
