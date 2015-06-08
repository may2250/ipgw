
#include "list.h"

#ifndef _DATASTRUCT_DEFINE_H_
#define _DATASTRUCT_DEFINE_H_

#define FALSE   0
#define TRUE    1

#pragma pack(1)

typedef struct Commdes_st
{
	int userNew; // 用户自定义内容
	int index;
	int tag;
	int dataLen;	
	unsigned char *data;
}Commdes_t;

typedef struct DataStream_st
{
	int userNew; // 用户自定义内容
	int index;
	int inChn;
	int streamType;
	int inPid;
	int outPid;
	int desNodeLen;
	Commdes_t *desNode; // Commdes_st
}DataStream_t;


//Dev_prgInfo_st
typedef struct Dev_prgInfo_t

{
    int userNew; // 用户自定义内容
    int index;
    int prgNum;		//2字节
    int chnId;		//1字节
    int streamId;	//2字节
    int networkId;	//2字节
    int pmtPid;		//2字节
    int oldPcrPid;		//2字节
    int newPcrPid;		//2字节
	int pmtDesListLen;
	Commdes_t *pmtDesList; // Commdes_st

	int pdataStreamListLen;
	DataStream_t *pdataStreamList; // DataStream_st

	//9.	节目名字长度//1字节
	//10.	具体的节目名字内容
	int  prgNameLen;
	unsigned char *prgName;
	//11.	服务提供商名字长度
	//12.	服务提供商名字
	int providerNameLen;
	char *providerName;
	int serviceType;
	//13.	CA标志
	int isCrypto;
	int psdtDesListLen;
	Commdes_t *psdtDesList; // Commdes_st

} Dev_prgInfo_st;

typedef struct IpGWDbSt
{
    int devNetFun;
    int dvbIptvMode; // 0=mpts, 1=spts
    int ttl;
} IpGWDbSt_st;

typedef struct UcIpSrcDbSt
{
    int netInterfaceMode;
    unsigned char ip[4];
    int port;
    unsigned char mac[6];
} UcIpSrcDbSt_st;

typedef struct ChannelProgramt
{
	int channelId;
	list_t prgNodes; // struct Dev_prgInfo_st
	//Chn_ca_st caNode;
	//list_t userPrgNodes; // struct User_prgInfo_t
	//list_t dtPidList; // MuxPidInfo_st , 透传表, 数组以输出通道为序
}ChannelProgramSt;

typedef struct  ClsProgram_t
{
	int _intChannelCntMax;
	int _outChannelCntMax;
	int _pmtMaxCnt; // = 29;
	list_t  inPrgList;  //ChannelProgramSt  8 input
	list_t outPrgList;  // 2 output
	int *chnBypass2; // 通道直通, 0=禁用，other=输出直通某个输出
	int *chnBypassEnable; // 通道直通功能激活
	int needInputData[2][8]; // 标志需要用到输入通道的数据，当数据丢失时报警
	int prgNum_min; // = 1;
    int prgPid_min; // = 0x100;
    int prgPid_max; // = 0xfff;
    int subPrgPid_min; // = 0x1000;
    int subPrgPid_max; // = 0x1ff0;
    int *m_autoMuxStartPid; // 自动映射起始PID _outChannelCntMax=2 为数量
    // ClsMux muxer = null;
    list_t **PrgPmtMuxList; // MuxPrgInfoGet_st  list Array
    list_t **PrgAVMuxList;  // list Array MuxPidInfo_st , 节目映射PID, 数组以输出通道为序
    list_t NitSection; // list Array Nit_section_st
    IpGWDbSt_st *ipGwDb;
}ClsProgram_st;

typedef struct  ClsGlobal_t{
    int _moduleBaseCmd;
    int _moduleId;
    UcIpSrcDbSt_st *_ucDb;
    IpGWDbSt_st *ipGwDb;
}ClsGlobal_st;

#pragma pack()

#endif	

