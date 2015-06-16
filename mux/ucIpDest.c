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
        free(clsGlobal._ucDb4->prgList);
        clsGlobal._ucDb4->prgList = NULL;
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
            }else{
                ucDb->prgList = NULL;
            }
        }else{
            ucDb->prgList = NULL;
        }
    }else{
        ucDb->prgList = NULL;
    }
    list_append(ucDblist, ucDb);
}

void SetDb3(int index){
    int i = 0;
    UcIpDestDbSt3_st *ucDb = NULL;
    list_get(clsGlobal.ucIpDestDb, index, &ucDb);
    memcpy(clsGlobal._ucDb4->ip, ucDb->ip, 4);
    memcpy(clsGlobal._ucDb4->mac, ucDb->mac, 6);
    clsGlobal._ucDb4->outMode = ucDb->outMode;
    clsGlobal._ucDb4->port = ucDb->port;
    clsGlobal._ucDb4->outputEnable = ucDb->outputEnable;
    clsGlobal._ucDb4->outChn = 0;
    if (ucDb->prgList != NULL)
    {
        freeUcIpDestPrg(clsGlobal._ucDb4->prgList);
        free(clsGlobal._ucDb4->prgList);
        clsGlobal._ucDb4->prgList = NULL;
        if (clsGlobal._ucDb4->prgList == NULL){
            clsGlobal._ucDb4->prgList = malloc(sizeof(list_t));
            list_init(clsGlobal._ucDb4->prgList);
        }
        UcIpDestPrgMuxInfoSt_st *eachPrg = NULL;
        for(i=0;i<list_len(ucDb->prgList);i++){
            list_get(ucDb->prgList, i, &eachPrg);
            UcIpDestPrgMuxInfoSt_st *curPrg = malloc(sizeof(UcIpDestPrgMuxInfoSt_st));
            if(eachPrg->avPidListLen > 0){
                curPrg->avPidListLen = eachPrg->avPidListLen;
                curPrg->avPidList = malloc(sizeof(eachPrg->avPidListLen));
                memcpy(curPrg->avPidList, eachPrg->avPidList, eachPrg->avPidListLen);
            }
            curPrg->inChn = eachPrg->inChn;
            curPrg->pmtPID = eachPrg->pmtPID;
            curPrg->prgId = eachPrg->prgId;
            list_append(clsGlobal._ucDb4->prgList, curPrg);
        }
    }
}

int ParamsWrite_dvbIptvMode(char *ip, int outMode){
    unsigned char cmdBytes[3] = { 0xf2, 0, 1 };
    return ParamWriteInt(ip, cmdBytes, 3, outMode, 1);
}

int ParamsWrite_ttl(char *ip, int ttl){
    unsigned char cmdBytes[3] = { 0xf2, 0, 2 };
    return ParamWriteInt(ip, cmdBytes, 3, ttl, 1);
}

// 发送设备参数
int ParamsWriteAll(char *ip, int bitMask){
    int isGood = 1, i = 0, j = 0;
    if ((bitMask & 0x2) !=0)
        isGood &= ParamWriteByBytesCmd(ip, (unsigned char)1, clsGlobal._ucDb4->ip, 4);
    if (clsGlobal._ucDb4->outMode < 3)//m_multicastEnable &&
    {
        if ((bitMask & 0x4) != 0)
            isGood &= ParamWriteByBytesCmd(ip, (unsigned char)2, clsGlobal._ucDb4->mac, 6);
    }

    if ((bitMask & 0x8) != 0)
        isGood &= ParamWriteByIntCmd(ip, (unsigned char)3, clsGlobal._ucDb4->port, 2);
    if ((bitMask & 0x10) != 0)
        isGood &= ParamWriteByIntCmd(ip, (unsigned char)4, clsGlobal._ucDb4->outMode, 1);

    if (1)//m_supportOutputEnable || m_autoEnableByPrgCnt
    {
        if ((bitMask & 0x20) != 0){
            isGood &= ParamWriteByIntCmd(ip, (unsigned char)5, clsGlobal._ucDb4->outputEnable, 1);
        }
    }
    if (1 && ((bitMask & 0x40) != 0))//m_supportPrgMuxInfo &&
    {
        unsigned char muxPrgBytes[128] = {0};
        UcIpDestPrgMuxInfoSt_st *eachPrg = NULL;
        int ia = 0;

//        if (0)//m_supportMultiMux
//        {
//            isGood &= ParamWriteByBytesCmd((byte)UcIpDest_cmd.prgMuxInfoMultiChnId, _ucDb.outChn, 1);
//        }
        if (clsGlobal._ucDb4->prgList != NULL ){
            if(list_len(clsGlobal._ucDb4->prgList) > 0){
                list_get(clsGlobal._ucDb4->prgList, 0, &eachPrg);
                muxPrgBytes[0] = 1;
                muxPrgBytes[1] = (unsigned char)(eachPrg->inChn);
                muxPrgBytes[2] = (unsigned char)(eachPrg->prgId);
                muxPrgBytes[3] = (unsigned char)(eachPrg->prgId >> 8);
            }
        }

        isGood &= ParamWriteByBytesCmd(ip, (unsigned char)6, muxPrgBytes, sizeof(muxPrgBytes));

        if (0)//m_supportIPTVInfo
        {
            ia = 0;
            eachPrg = NULL;
            if (clsGlobal._ucDb4->prgList != NULL && list_len(clsGlobal._ucDb4->prgList) > 0){
                muxPrgBytes[ia++] = (unsigned char)list_len(clsGlobal._ucDb4->prgList);
                for(i=0;i<list_len(clsGlobal._ucDb4->prgList);i++){
                    list_get(clsGlobal._ucDb4->prgList, i , &eachPrg);
                    muxPrgBytes[ia++] = (unsigned char)(eachPrg->prgId);
                    muxPrgBytes[ia++] = (unsigned char)(eachPrg->prgId >> 8);
                    muxPrgBytes[ia++] = (unsigned char)(eachPrg->pmtPID);
                    muxPrgBytes[ia++] = (unsigned char)(eachPrg->pmtPID >> 8);
                    if (eachPrg->avPidListLen == 0){
                        muxPrgBytes[ia++] = 0;
                    }else{
                        muxPrgBytes[ia++] = (unsigned char)(eachPrg->avPidListLen);
                        for(j=0;j<eachPrg->avPidListLen;j++){
                            muxPrgBytes[ia++] = (unsigned char)(eachPrg->avPidList[j]);
                            muxPrgBytes[ia++] = (unsigned char)(eachPrg->avPidList[j] >> 8);
                        }
                    }
                }
            }else{
                muxPrgBytes[ia++] = 0;
            }
            isGood &= ParamWriteByBytesCmd(ip, (unsigned char)7, muxPrgBytes, ia);
        }

    }

    if (isGood)
    {
        if ((bitMask & 0x1) != 0 || (bitMask & 0x20) != 0){
            isGood &= ParamWriteByIntCmd(ip, (unsigned char)0xf0, 0, 0);
        }

//        if (!m_applyBackEnable)
//        {
//            isGood = 1;
//        }
//
//        if (isGood)
//        {
//            RefreshPlayBtn();
//        }
//        else
//        {
//            btn_play.Visible = false;
//        }
    }
    return isGood;
}
