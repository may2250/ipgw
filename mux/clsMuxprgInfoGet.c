#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "datastructdef.h"
#include "communicate.h"
#include "clsMuxprgInfoGet.h"

extern ClsProgram_st clsProgram;


int LittleFormat_fromBytes(int offset, int length, char *inBytes)
{
    int rtnInt = 0, i = 0;
    for (i = 0; i < length; i++)
    {
        rtnInt += inBytes[offset++] << (i * 8);
    }
    return rtnInt;
}

int BigFormat_fromBytes(int offset, int length, char *inBytes)
{
    int rtnInt = 0, i = 0;
    for (i = 0; i < length; i++)
    {
        rtnInt <<= 8;
        rtnInt += inBytes[offset++];
    }
    return rtnInt;
}

int GetSearchingStatus(char *ip, int inChn)
{
    int iAddr = 0;
    int rlen=0;
    unsigned char sendbuf[20];
    unsigned char buf[1024];
    sendbuf[iAddr++] = 0x77;
    sendbuf[iAddr++] = 0x6C;
    sendbuf[iAddr++] = 0x11;
    sendbuf[iAddr++] = 0;
    sendbuf[iAddr++] = (unsigned char)inChn;

    communicate(ip, sendbuf, iAddr, buf, &rlen);
    if(rlen <= iAddr){
        return -1;
    }
    int rtnValue = buf[iAddr];
    return rtnValue;

}

int Search(char *ip, int inChn)
{
    unsigned char buf[1024];
    int i = 0, j=0;
    unsigned char sendbuf[1024];
    int iAddr = 0;
    int rlen=0;
    //byte[] cmdBytes = new byte[20];
    sendbuf[iAddr++] = 0x77;
    sendbuf[iAddr++] = 0x6C;
    sendbuf[iAddr++] = 0x11;
    sendbuf[iAddr++] = 1;
    sendbuf[iAddr++] = (unsigned char)inChn;

    communicate(ip, sendbuf, iAddr, buf, &rlen);
    if(rlen <= iAddr){
        //搜索失败
        return 3;
    }
    int rtnValue = buf[iAddr];
    if (rtnValue != 0)
        return 3;

    int searchStatus = -1;
    //DateTime startTime = DateTime.Now;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    int startTimeMinute = timeinfo->tm_min;
    while (1)
    {
        usleep(200);
        searchStatus = GetSearchingStatus(ip, inChn);
        if (searchStatus != 1)
        {
            break;
        }
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        int endTimeMinute = timeinfo->tm_min;
        if (endTimeMinute < startTimeMinute)
            endTimeMinute += 60;
        if (endTimeMinute - startTimeMinute > 3)
        {
            break;
        }
    }

    if (searchStatus == 2)
        return 0;
    else
        return 3;
}

int getPrgCnt(char *ip, int inChn,  int * result)
{
    char buf[7];
    int i = 0;
    char sendbuf[6];
    int rlen=0;

    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x11;
    sendbuf[3]=0x02;
    sendbuf[4]=(unsigned char)inChn;
    sendbuf[5]=0x00;

    communicate(ip, sendbuf, 6, buf, &rlen);

    //printf("\n####Recive Convert getPrgCnt nums=[%d]\n",rlen );

    if( 7 == rlen ){

        //0 auto 1 manual
        *result = (int)buf[6];
       // printf("okkkkkkkkkkkkkkkkkkkkkkkk\n");
        return *result;
    }

    return -1;
}

int getPrgramInfo(char *ip, int inChn, int prgNo, unsigned char * result, int * reslen)
{

    char buf[256];
    int i = 0;
    char sendbuf[6];
    int rlen=0;

    //get call 0 auto 1 manual signal status
    sendbuf[0]=0x77;
    sendbuf[1]=0x6C;
    sendbuf[2]=0x11;
    sendbuf[3]=0x02;
    sendbuf[4]=(unsigned char)inChn;
    sendbuf[5]=(unsigned char)prgNo;

    for(i=0;i<6;i++)
   //printf("%x ", sendbuf[i]);
    memset(buf,0,sizeof(buf));
    communicate(ip, sendbuf, 6, buf, &rlen);

    //printf("\n####Recive Convert getPrgramInfo nums=[%d]\n",rlen );

    if( rlen > 6 ){
        memcpy(result, buf, rlen);
       // printf("\n###112221#R\n");
        *reslen =  rlen;
        return *reslen;
    }
    else if(rlen >=0 && rlen < 6){
        return *reslen;
    }

    return -1;
}

int getPrograms(char *ip, int inChn, list_t *prginfolist)
{
    unsigned char buf[256];
    unsigned char idstr[32] = {0};
    int i = 0, j=0, k=0, p=0, o=0, iPrg=0;
    char sendbuf[256];
    int rlen=0;
    unsigned char *ptemp = NULL;
    int ibuflen = 0;
    int iPmtCntIndex = 1;
    unsigned short itmp;
	int iAddr = 0;
    int jtmp=0;
    Dev_prgInfo_st *ptmpPrgInfo = NULL;

    //getProCnt
    int result=0;
    int prgCnt = getPrgCnt(ip, inChn, &result);

    //printf("prgCnt=%d\n", prgCnt);

    if (prgCnt > 0)
    {
        list_init(prginfolist);

        for (iPrg = 0; iPrg < prgCnt; iPrg++){


            iAddr = 0;
            memset(buf,0,sizeof(buf));
            rlen = getPrgramInfo(ip, inChn, iPrg+1, buf, &ibuflen);
            //invalid program

            if(rlen >=0 && rlen <6) {
        //        printf("\n###1ipmt1#R\n");
             iPmtCntIndex++; continue;
             }
			if(rlen < 0){return rlen;}

            if(rlen > 0){

				ptmpPrgInfo = malloc(sizeof(Dev_prgInfo_st));

                ptmpPrgInfo->index = iPmtCntIndex++;
				iAddr += 4; //skip 6 header to data pointer

				iAddr += 2; //n
				ptmpPrgInfo->prgNum = buf[iAddr + 1]<<8 | buf[iAddr];//n
                iAddr += 2;

				ptmpPrgInfo->chnId = buf[iAddr]; //n
                iAddr += 1;
				ptmpPrgInfo->streamId = buf[iAddr + 1]<<8 | buf[iAddr];//n
                iAddr += 2;
				ptmpPrgInfo->networkId = buf[iAddr + 1]<<8 | buf[iAddr];//n

                iAddr += 2;
				ptmpPrgInfo->pmtPid = buf[iAddr + 1]<<8 | buf[iAddr];//n

                iAddr += 2;
				if (ptmpPrgInfo->pmtPid == 0xffff) continue;
				ptmpPrgInfo->oldPcrPid = buf[iAddr + 1]<<8 | buf[iAddr];//n
                ptmpPrgInfo->newPcrPid = ptmpPrgInfo->oldPcrPid;
                iAddr += 2;
                int pmtDesCnt = buf[iAddr];
                iAddr += 1;

                //pmt
				ptmpPrgInfo->pmtDesListLen = pmtDesCnt;
                ptmpPrgInfo->pmtDesList = malloc(pmtDesCnt * sizeof(Commdes_t) );
                int desCntIndex = 1;
                Commdes_t *pmtDesInfo = ptmpPrgInfo->pmtDesList;


                for (i = 0; i < pmtDesCnt; i++)
                {
                    pmtDesInfo->index = desCntIndex++;
                    pmtDesInfo->tag = buf[iAddr];
                    iAddr += 1;
                    int pmtDesDataLen = buf[iAddr];
                    pmtDesInfo->dataLen = pmtDesDataLen;
                    iAddr += 1;
                    pmtDesInfo->data = malloc(pmtDesDataLen);
					memcpy(pmtDesInfo->data, buf+iAddr, pmtDesDataLen);
                    iAddr += pmtDesDataLen;
                    pmtDesInfo++;
                }

                //stream data
                int dataStreamCnt = buf[iAddr];
                iAddr += 1;
				ptmpPrgInfo->pdataStreamListLen = dataStreamCnt;
                ptmpPrgInfo->pdataStreamList = malloc(dataStreamCnt * sizeof(DataStream_t));
                DataStream_t *pdataStreamInfo = ptmpPrgInfo->pdataStreamList;


                //printf("====+++DataStream_t num =%d\n", dataStreamCnt);

                for (i = 0; i < dataStreamCnt; i++)
                {
                    pdataStreamInfo->inChn = ptmpPrgInfo->chnId;
                    pdataStreamInfo->index = desCntIndex++;
                    pdataStreamInfo->streamType = buf[iAddr];
					iAddr += 1;
					pdataStreamInfo->inPid = buf[iAddr + 1]<<8 | buf[iAddr];//n

                    pdataStreamInfo->outPid = pdataStreamInfo->inPid;

                    iAddr += 2;

                    int dataStreamDesCnt = buf[iAddr];
					iAddr += 1;
					pdataStreamInfo->desNodeLen = dataStreamDesCnt;
                    pdataStreamInfo->desNode = malloc(dataStreamDesCnt * sizeof(Commdes_t));
                    Commdes_t *pdataStreamDesInfo = pdataStreamInfo->desNode;
					int subDesCntIndex = 1;

                    int k=0;

                    for (j = 0; j < dataStreamDesCnt; j++)
                    {
                        pdataStreamDesInfo->index = subDesCntIndex++;
                        pdataStreamDesInfo->tag = buf[iAddr];
						iAddr += 1;
                        int dataStreamDesDataLen = buf[iAddr];
						iAddr += 1;
						pdataStreamDesInfo->dataLen = dataStreamDesDataLen;
                        pdataStreamDesInfo->data = malloc(dataStreamDesDataLen);
                        memcpy(pdataStreamDesInfo->data, buf+iAddr, dataStreamDesDataLen);


						iAddr += dataStreamDesDataLen;
						pdataStreamDesInfo++;
                    }
                    pdataStreamInfo++;
                }

                // --- 节目和提供商名字 ---
                int prgNameLen = buf[iAddr];
                iAddr += 1;
                ptmpPrgInfo->prgNameLen = prgNameLen;
                //stan bug bug
                ptmpPrgInfo->prgName = (unsigned char *)malloc(prgNameLen);
                memset(ptmpPrgInfo->prgName, 0,  prgNameLen);
                memcpy(ptmpPrgInfo->prgName, (unsigned char *)(buf+iAddr),  prgNameLen);

                iAddr += prgNameLen;
                int providerNameLen = buf[iAddr];
                iAddr += 1;
                ptmpPrgInfo->providerNameLen = providerNameLen;
                ptmpPrgInfo->providerName = (unsigned char *)malloc(ptmpPrgInfo->providerNameLen);
                memcpy(ptmpPrgInfo->providerName, buf+iAddr, providerNameLen);

                iAddr += providerNameLen;
                ptmpPrgInfo->isCrypto = buf[iAddr] > 0 ? 1 : 0;
                iAddr += 1;

                //SDT 描述符
                int sdtDesCnt = buf[iAddr];
                iAddr += 1;
				ptmpPrgInfo->psdtDesListLen = sdtDesCnt;
                ptmpPrgInfo->psdtDesList = malloc(sdtDesCnt * sizeof(Commdes_t));
                Commdes_t *psdtDesInfo = ptmpPrgInfo->psdtDesList;

                for (i = 0; i < sdtDesCnt; i++)
                {
                    psdtDesInfo->index = desCntIndex++;
                    psdtDesInfo->tag = buf[iAddr];
                    iAddr += 1;
                    int sdtDesDataLen = buf[iAddr];
                    iAddr += 1;
					psdtDesInfo->dataLen = sdtDesDataLen;
                    psdtDesInfo->data = malloc(sdtDesDataLen);
                    memcpy(psdtDesInfo->data, buf+iAddr, sdtDesDataLen);
					iAddr += sdtDesDataLen;
                    if (psdtDesInfo->tag == 0x48)
                        ptmpPrgInfo->serviceType = psdtDesInfo->data[0];

                    psdtDesInfo++;
                }


                list_append(prginfolist, ptmpPrgInfo);

			}
        }
		return 1;
    }

    return 0;
}

int CheckReturnBytes(char *cmdHeadBytes, int headLen, char *rtnBytes, int rtnBytesLen)
{
    int j = 0;
    if (rtnBytesLen <= headLen)
        return 2;
    for ( j = 0; j < headLen; j++)
    {
        if (cmdHeadBytes[j] != rtnBytes[j])
        {
            return 3;
        }
    }
    return 0;
}

