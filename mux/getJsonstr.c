#include <stdio.h>
#include <stdlib.h>
#include "getJsonstr.h"

extern ClsProgram_st clsProgram;
extern ClsGlobal_st  clsGlobal;

void getPrgsJson(char *ip, char *outprg){
    int i = 0, j = 0, res = 0, inChn = 1;
    char str[200] = {0};
    char idstr[100] = {0};
    Dev_prgInfo_st *ptmpPrgInfo= NULL;
    Dev_prgInfo_st *PrgInfo;
    ChannelProgramSt *pst = NULL;
    //释放输入通道节目占用的内存
    list_get(&(clsProgram.inPrgList), 0, &pst);
    if( list_len(&pst->prgNodes) > 0){
        freePrograms(&pst->prgNodes);
    }
    res = getPrograms(ip, 1, &pst->prgNodes);
    if(0 != res){
        cJSON *prgjson,*channelsarray,*channeljson,*subprgjson,*subprgsarray,*streamjson,*streamsarray,*audiosarray,*prgsarray;//*prgsjson,
        char* prgjsonstring;
        channelsarray = cJSON_CreateArray();
        cJSON_AddItemToArray(channelsarray,channeljson = cJSON_CreateObject());
        cJSON_AddTrueToObject(channeljson,"folder");
        cJSON_AddTrueToObject(channeljson,"expanded");
        sprintf(idstr, "id1.%d", inChn);//1.2
        cJSON_AddStringToObject(channeljson,"key", idstr);
        cJSON_AddStringToObject(channeljson,"icon", "img/channel_in.ico");
        cJSON_AddItemToObject(channeljson, "children", prgsarray = cJSON_CreateArray());
        for(i=0; i<list_len(&pst->prgNodes); i++) {
            cJSON_AddItemToArray(prgsarray,prgjson = cJSON_CreateObject());
            ptmpPrgInfo = NULL;
            list_get(&pst->prgNodes, i, &ptmpPrgInfo);
            //添加节目节点TITLE
            memset(idstr, 0, sizeof(idstr));
            memcpy(idstr, ptmpPrgInfo->prgName, ptmpPrgInfo->prgNameLen);
            sprintf(str,"节目%d(0X%x):PID(0X%x) PCR_PID(0X%x) - %s",ptmpPrgInfo->prgNum, ptmpPrgInfo->prgNum, ptmpPrgInfo->pmtPid, ptmpPrgInfo->newPcrPid, idstr );
            memset(idstr, 0, sizeof(idstr));
            cJSON_AddStringToObject(prgjson,"title", str);
            cJSON_AddStringToObject(prgjson,"tooltip", str);
            cJSON_AddTrueToObject(prgjson,"folder");
            cJSON_AddFalseToObject(prgjson,"expanded");
            cJSON_AddNumberToObject(prgjson, "index", ptmpPrgInfo->index);
            cJSON_AddNumberToObject(prgjson, "pmtPid", ptmpPrgInfo->pmtPid);
            cJSON_AddNumberToObject(prgjson, "chnid", ptmpPrgInfo->chnId);
            sprintf(idstr, "id1.%d.%d", inChn, ptmpPrgInfo->index);//1.2.1
            cJSON_AddStringToObject(prgjson,"key", idstr);
            cJSON_AddStringToObject(prgjson,"icon", "img/notebook.ico");

            cJSON_AddItemToObject(prgjson, "children", subprgsarray = cJSON_CreateArray());
            //subprgjson
            cJSON_AddItemToArray(subprgsarray,subprgjson = cJSON_CreateObject());
            cJSON_AddStringToObject(subprgjson,"title", "maximun bitrate descriptor");
            cJSON_AddTrueToObject(subprgjson,"folder");
            cJSON_AddFalseToObject(subprgjson,"expanded");
            sprintf(idstr, "id1.%d.%d.1", inChn, ptmpPrgInfo->index);
            cJSON_AddStringToObject(subprgjson,"key", idstr);
            cJSON_AddStringToObject(subprgjson,"icon", "img/channel_in.ico");

            cJSON_AddItemToArray(subprgsarray,subprgjson = cJSON_CreateObject());
            sprintf(idstr, "id1.%d.%d.2", inChn, ptmpPrgInfo->index);
            cJSON_AddStringToObject(subprgjson,"title", "multiplex buffer utilization descriptor");
            cJSON_AddTrueToObject(subprgjson,"folder");
            cJSON_AddFalseToObject(subprgjson,"expanded");
            cJSON_AddStringToObject(subprgjson,"key", idstr);
            cJSON_AddStringToObject(subprgjson,"icon", "img/channel_in.ico");
            int j=0, k=0;
            //PMT
            Commdes_t *tmpinfo = malloc(sizeof(Commdes_t));
            int offset = 0, flag = 0;
            for(j=0; j<ptmpPrgInfo->pmtDesListLen; j++) {
                memcpy(tmpinfo, ptmpPrgInfo->pmtDesList+offset, sizeof(Commdes_t) );
                offset += 1;
            }
            free(tmpinfo);
            //stream
            offset = 0;
            DataStream_t *streaminfo = malloc(sizeof(DataStream_t));
            for(j=0; j<ptmpPrgInfo->pdataStreamListLen; j++) {
                memcpy(streaminfo, ptmpPrgInfo->pdataStreamList+offset, sizeof(DataStream_t) );
                //printf("-----%x-->>%x\n", streaminfo->inPid, streaminfo->streamType);
                offset += 1;
                if(2 == streaminfo->streamType){
                    //MPEG2 VIDEO
                    cJSON_AddItemToArray(subprgsarray,subprgjson = cJSON_CreateObject());
                    sprintf(idstr, "id1.%d.%d.%d", inChn, ptmpPrgInfo->index, streaminfo->index);
                    sprintf(str,"MPEG2 VIDEO  [PID(0x%x)]",  streaminfo->inPid);
                    cJSON_AddStringToObject(subprgjson,"title", str);
                    cJSON_AddTrueToObject(subprgjson,"folder");
                    cJSON_AddFalseToObject(subprgjson,"expanded");
                    cJSON_AddNumberToObject(subprgjson, "index", streaminfo->index);
                    cJSON_AddStringToObject(subprgjson,"key", idstr);
                    cJSON_AddStringToObject(subprgjson,"icon", "img/favicon.ico");

                    cJSON_AddItemToObject(subprgjson, "children", streamsarray = cJSON_CreateArray());
                    cJSON_AddItemToArray(streamsarray,streamjson = cJSON_CreateObject());
                    sprintf(idstr, "id1.%d.%d.%d.1", inChn,  ptmpPrgInfo->index, streaminfo->index);
                    cJSON_AddStringToObject(streamjson,"title", "video stream descriptor");
                    cJSON_AddTrueToObject(streamjson,"folder");
                    cJSON_AddFalseToObject(streamjson,"expanded");
                    cJSON_AddStringToObject(streamjson,"key", idstr);
                    cJSON_AddStringToObject(streamjson,"icon", "img/channel_in.ico");

                }else if(4 == streaminfo->streamType){
                    //MPEG2 AUDIO
                    cJSON_AddItemToArray(subprgsarray,subprgjson = cJSON_CreateObject());
                    sprintf(idstr, "id1.%d.%d.%d", inChn, ptmpPrgInfo->index, streaminfo->index);
                    sprintf(str,"MPEG2 AUDIO  [PID(0x%x)]",  streaminfo->inPid);
                    cJSON_AddStringToObject(subprgjson,"title", str);
                    cJSON_AddTrueToObject(subprgjson,"folder");
                    cJSON_AddFalseToObject(subprgjson,"expanded");
                    cJSON_AddNumberToObject(subprgjson, "index", streaminfo->index);
                    cJSON_AddStringToObject(subprgjson,"key", idstr);
                    cJSON_AddStringToObject(subprgjson,"icon", "img/audio.ico");

                    //stream json
                    cJSON_AddItemToObject(subprgjson, "children", audiosarray = cJSON_CreateArray());
                    cJSON_AddItemToArray(audiosarray,streamjson = cJSON_CreateObject());
                    sprintf(idstr, "id1.%d.%d.%d.1", inChn, ptmpPrgInfo->index, streaminfo->index);
                    cJSON_AddStringToObject(streamjson,"title", "ISO 639 language descriptor");
                    cJSON_AddTrueToObject(streamjson,"folder");
                    cJSON_AddFalseToObject(streamjson,"expanded");
                    cJSON_AddStringToObject(streamjson,"key", idstr);
                    cJSON_AddStringToObject(streamjson,"icon", "img/channel_in.ico");

                    cJSON_AddItemToArray(audiosarray,streamjson = cJSON_CreateObject());
                    sprintf(idstr, "id1.%d.%d.%d.2", inChn, ptmpPrgInfo->index, streaminfo->index);
                    cJSON_AddStringToObject(streamjson,"title", "audio stream descriptor");
                    cJSON_AddTrueToObject(streamjson,"folder");
                    cJSON_AddFalseToObject(streamjson,"expanded");
                    cJSON_AddStringToObject(streamjson,"key", idstr);
                    cJSON_AddStringToObject(streamjson,"icon", "img/channel_in.ico");
                }
                Commdes_t *desNodeinfo = malloc(sizeof(Commdes_t));
                for(k=0; k<streaminfo->desNodeLen; k++) {
                    memcpy(desNodeinfo, streaminfo->desNode+flag, sizeof(Commdes_t) );
                    //memset(tmpstr, 0, sizeof(tmpstr));
                    //memcpy(tmpstr, desNodeinfo->data, desNodeinfo->dataLen );
                    //printf("---desNodeinfo--%d-->>%d::::%d:::%d:::%d\n", streaminfo->desNodeLen, tmpstr[0],tmpstr[1],tmpstr[2],tmpstr[3]);
                    flag += 1;

                }
                free(desNodeinfo);
            }
            free(streaminfo);
        }

        //添加通道节点TITLE
        sprintf(str,"通道%d(ASI)", inChn);
        cJSON_AddStringToObject(channeljson,"title", str);

        prgjsonstring = cJSON_PrintUnformatted(channelsarray);

        memcpy(outprg, prgjsonstring, strlen(prgjsonstring));
        printf("---prgjsonlen--->>>%d\n",strlen(prgjsonstring));
        //释放内存
        cJSON_Delete(channelsarray);
        free(prgjsonstring);
    }else{
        cJSON *channelsarray,*channeljson;
        char* prgjsonstring;
        channelsarray = cJSON_CreateArray();
        cJSON_AddItemToArray(channelsarray,channeljson = cJSON_CreateObject());
        cJSON_AddTrueToObject(channeljson,"folder");
        cJSON_AddTrueToObject(channeljson,"expanded");
        sprintf(idstr, "id1.%d", inChn);//1.2
        cJSON_AddStringToObject(channeljson,"key", idstr);
        cJSON_AddStringToObject(channeljson,"icon", "img/channel_in.ico");
        //添加通道节点TITLE
        sprintf(str,"通道%d(ASI)", inChn);
        cJSON_AddStringToObject(channeljson,"title", str);
        prgjsonstring = cJSON_PrintUnformatted(channelsarray);
        memcpy(outprg, prgjsonstring, strlen(prgjsonstring));

        //释放内存
        cJSON_Delete(channelsarray);
        free(prgjsonstring);
    }

}

void getbaseJson(char *ip, char *outprg){
	cJSON *baseinfo = cJSON_CreateObject();
	char *prgjsonstring;
	char str[8] = {0};
	char srcip[16] = {0};
	unsigned int devType = 0, HardVersion = 0, SoftVersion = 0, FpgaVersion = 0, port = 0, outip = 0;
	getDeviceType(ip, &devType);
	printf("---------------devType===%x\n", devType);
	sprintf(str,"%x", devType);
	if(strcmp("101", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "8合2复用器");
	}else if(strcmp("102", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "8合1复用器");
	}else if(strcmp("201", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "4合1QAM调制器");
	}else if(strcmp("211", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "4合1QAM调制器9789");
	}else if(strcmp("202", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "QPSK转QAM调制器");
	}else if(strcmp("203", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "单路QAM调制器");
	}else if(strcmp("213", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "单路QAM调制器9789");
	}else if(strcmp("204", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "HQAM调制器");
	}else if(strcmp("301", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "单路编码器");
	}else if(strcmp("311", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "单路编码器(86391)");
	}else if(strcmp("302", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "四路编码器");
	}else if(strcmp("312", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "四路编码器(86391)");
	}else if(strcmp("303", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "高清编码器");
	}else if(strcmp("306", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "8合1标清H264编码器");
	}else if(strcmp("401", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "四路TS流卫星接收机");
	}else if(strcmp("501", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "IP网关，TS转IP");
	}else if(strcmp("502", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "IP网关，IP转TS");
	}else if(strcmp("503", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "IP网管，TS-IP双向单路");
	}else if(strcmp("601", str)){
		cJSON_AddStringToObject(baseinfo,"devType", "标准加扰机");
	}else{
		cJSON_AddStringToObject(baseinfo,"devType", "unkown");
	}

	prgjsonstring = cJSON_PrintUnformatted(baseinfo);
	memcpy(outprg, prgjsonstring, strlen(prgjsonstring));

	//释放内存
	cJSON_Delete(baseinfo);
	free(prgjsonstring);
}

int getIpReadJson(char *ip, char *outprg){
    if(IpRead(ip)){
        return 1;
    }
    cJSON *baseinfo = cJSON_CreateObject();
    char *prgjsonstring;
    char str[32] = {0};
    sprintf(str,"%d.%d.%d.%d", clsGlobal._ucDb->ip[0], clsGlobal._ucDb->ip[1],clsGlobal._ucDb->ip[2],clsGlobal._ucDb->ip[3]);
    cJSON_AddStringToObject(baseinfo,"srcip", str);
    memset(str, 0, sizeof(str));
    sprintf(str,"%x:%x:%x:%x:%x:%x\n", clsGlobal._ucDb->mac[0], clsGlobal._ucDb->mac[1],clsGlobal._ucDb->mac[2],clsGlobal._ucDb->mac[3],clsGlobal._ucDb->mac[4],clsGlobal._ucDb->mac[5]);
    cJSON_AddStringToObject(baseinfo,"mac", str);
    cJSON_AddNumberToObject(baseinfo,"port", clsGlobal._ucDb->port);
    cJSON_AddNumberToObject(baseinfo,"netInterfaceMode", clsGlobal._ucDb->netInterfaceMode);
    cJSON_AddNumberToObject(baseinfo,"dvbIptvMode", clsGlobal.ipGwDb->dvbIptvMode);
    cJSON_AddNumberToObject(baseinfo,"ttl", clsGlobal.ipGwDb->ttl);

    prgjsonstring = cJSON_PrintUnformatted(baseinfo);
    memcpy(outprg, prgjsonstring, strlen(prgjsonstring));

    //释放内存
    cJSON_Delete(baseinfo);
    free(prgjsonstring);
}

int getInputStsJson(char *ip, char *outprg){
    int lockStatus = 0, bitrate = 0;
    if(ReadInputStatus(ip, &lockStatus, &bitrate)){
        return 1;
    }
    cJSON *baseinfo = cJSON_CreateObject();
    char *prgjsonstring;
    char str[32] = {0};

    cJSON_AddNumberToObject(baseinfo,"lockStatus", lockStatus);
    cJSON_AddNumberToObject(baseinfo,"bitrate", bitrate);

    prgjsonstring = cJSON_PrintUnformatted(baseinfo);
    memcpy(outprg, prgjsonstring, strlen(prgjsonstring));

    //释放内存
    cJSON_Delete(baseinfo);
    free(prgjsonstring);
}