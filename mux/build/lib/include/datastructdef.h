
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
	//7.	PMT表描述个数 //1字节
	//For(i=0;i<n;i++)
	//{
	//    //描述标志  1字节
	////描述长度  1字节
	////描述内容
	//}
	int pmtDesListLen;
	Commdes_t *pmtDesList; // Commdes_st

	//8.	数据流个数 //1字节
	//For(i=0;i<n1;i++)
	//{
	//    //数据流类型  1字节
	////数据流PID  2字节
	//描述子个数 //1字节
	//For(i=0;i<n;i++)
	//{
	//    //描述标志  1字节
	////描述长度  1字节
	////描述内容
	//}
	//}
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
	//14.	SDT表描述子个数
	//For(i=0;i<n;i++)
	//{
	//    //描述标志  1字节
	////描述长度  1字节
	////描述内容
	//}
	int psdtDesListLen;
	Commdes_t *psdtDesList; // Commdes_st

} Dev_prgInfo_st;

typedef struct User_prgInfo_st
{
    int index;
    int prgNum;
    int streamId;
    int networkId;
    int pmtPid;
    int pcrPidInChn; // 指示pcrPid的来处
    int oldPcrPid;		//2字节
    int newPcrPid;		//2字节
    int prgNameLen;
    char *prgName;
    int providerNameLen;
    char *providerName;
    int serviceType;
    int pmtDesListLen;
    Commdes_t *pmtDesList; // Commdes_st
    int pdataStreamListLen;
    DataStream_t *pdataStreamList; // User_DataStream_st
    //13.	CA标志
    int isCrypto;
    //14.	SDT表描述子个数
    int psdtDesListLen;
    Commdes_t *psdtDesList; // Commdes_st
}User_prgInfo_t;


typedef struct __ts_table_pmt_es_t
{
	unsigned char		descriptor_flag;
	unsigned char	    descriptor_len;
	unsigned char       *descriptor;
	//struct __ts_table_pmt_es_t*		next;

}ts_table_pmt_es_t;


typedef struct out_program_num_s
{
	unsigned char inChn;       //1 byte
	unsigned char prgIndex;    //1 byte
	unsigned short newPrgId;   //2 byte
	unsigned short newPid;	   //2 byte
} out_program_num_t;



typedef struct DatabaseOutputChannel_t
{
	unsigned int outputRate;
	unsigned int oringal_networkid;
	unsigned int networkId;
	unsigned int streamId;
	unsigned char isAutoRaiseVersion;
	unsigned int version;
	unsigned char isManualMapMode;
	unsigned char isAutoRankPAT;

	unsigned char isNeedSend_pat;
	unsigned char isNeedSend_pmt;
	unsigned char isNeedSend_sdt;
	unsigned char isNeedSend_cat;
	unsigned char isNeedSend_nit;
}DatabaseOutputChannel_st;

typedef struct Database_t
{
	unsigned char isAutoMakeMux;
	unsigned char isAutoOutTreeListExpandAll;
	unsigned char isAutoInTreeListExpandAll;
	unsigned char isPrgInfoHexPid;
	unsigned char isConnectPid;
	unsigned char isLogEnable;
	int poutChnArrayLen;
	DatabaseOutputChannel_st *poutChnArray;

	//string net_ipAddrStr;
	//int net_port;
	//ConnectType_en net_type;
	int startPid;
	//bool isServerMode;

}Database_st;

typedef struct MuxPrgInfoGet_t
{
	int inChannel;
	int prgIndex; // 该消息指示的节目列表中消息的索引
	int prgNum;
	int prgPid;
}MuxPrgInfoGet_st;


typedef struct MuxPidInfo_t
{
	int inChannel;
	int oldPid;
	int newPid;
}MuxPidInfo_st;


typedef struct Chn_ca_t
{
	int version_number; // 5b
	list_t caIdenList; // CA_descriptor
}Chn_ca_st;

typedef struct ChannelProgramt
{
	int channelId;
	list_t prgNodes; // struct Dev_prgInfo_st
	Chn_ca_st caNode;
	list_t userPrgNodes; // struct User_prgInfo_t
	list_t dtPidList; // MuxPidInfo_st , 透传表, 数组以输出通道为序
}ChannelProgramSt;



 typedef struct patPrg_st
{
	 int program_number; // 16b
	 int reserved; // 3b
	 int pid; // 13b	  if(program_number == 0) pid == networkId;

}patPrg_t;

typedef struct pat_senction_t
{


	 int table_id; // 8b
	 int section_syntax_indicator; // 1b
	 int flag_0; // 1b
	 int reserved0; // 2b
	 int section_length; // 12b
	 int transport_stream_id; // 16b
	 int reserved1; // 2b
	 int version_number; // 5b
	 int current_next_indicator; // 1b
	 int section_number; // 8b
	 int last_section_number; // 8b
	 int patPrg_tListLen;
	 patPrg_t *patPrg_tList; 
	 int crc32; // 32b
}pat_senction_st;

typedef struct CA_descriptor_t
{
	 unsigned char userNew; // 用户自定义内容
	 int inChannel;
	 int index;
	 int tag;
	 int descriptor_length;	 
	 //int [] CA_system_id_list; // b16 for(;;)
	 int inCaSysId;
	 int outCaSysId;
	 int reserved;
	 int inCaPid;
	 int outCaPid;
	 int private_data_byte_len;
	 unsigned char *private_data_byte;
}CA_descriptor;

typedef struct pmt_senction_t
 {
	  int table_id; // 8b
	  int section_syntax_indicator; // 1b

	  int flag_0; // 1b
	  int reserved0; // 2b
	  int section_length; // 12b
	  int program_number; // 16b

	 int reserved1; // 2b
	 int version_number; // 5b
	 int current_next_indicator; // 1b
	 int section_number; // 8b
	 int last_section_number; // 8b

	 int reserved2; // 3b
	 int pcrPid; // 13b
	 int reserved3; // 4b
	 int program_info_length; // 12b
	 int pmtDesListLen;
	 Commdes_t *pmtDesList; // Commdes_st

	 int pdataStreamListLen;
	  DataStream_t *pdataStreamList; // DataStream_st
	  int crc32; // 32b

}pmt_senction_st;


typedef struct table_pmtList
{
	list_t table_pmt; 
}table_pmtList_st;

typedef struct BufferUn
{
	int bufLen;
	unsigned char *pbuf;
}BufferUn_st;

typedef struct ClsMux
{	
	list_t table_pat; //BufferUn_st*
	list_t table_pmtList; // list_t*
	list_t table_sdt; //BufferUn_st*
	list_t table_cat; //BufferUn_st*
	list_t table_nit;//BufferUn_st*
}ClsMux_st;


typedef struct  ClsProgram_t
{
	int _intChannelCntMax;
	int _outChannelCntMax;
	int _pmtMaxCnt; // = 29;
	list_t  inPrgList;  //ChannelProgramSt  8 input
	list_t outPrgList;  // 2 output
	int *chnBypass2; // 通道直通, 0=禁用，other=输出直通某个输出
	int *chnBypassEnable; // 通道直通功能激活
	// List<ScramblePrgSt> scramblePrgList;
	// List<ScramblePrgSt_v2> scramblePrgListV2;
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
	// Dglt_showPidMap dglt_showPidMap = null;
	 int pidMap_eachTransmit_numberMax;
}ClsProgram_st;	


typedef struct ClsParams
{	
	int channelNumMax;
	Database_st *pvalueTree;
}ClsParams_st; 

typedef struct sdtPrgName_t
{
	 int service_id; // 16b
	 int reserved_future_use; // 6b
	 int EIT_schedule_flag; // 1b
	 int EIT_present_following_flag; // 1b
	 int runing_status; // 3b
	 int free_CA_mode; // 1b
	 int descriptors_loop_length; // 12b
	int desListLen;
	Commdes_t *desList; // Commdes_st
}sdtPrgName_st;

typedef struct sdt_senction_t
{
	 int table_id; // 8b
	 int section_syntax_indicator; // 1b
	 int reserved_future_use1; // 1b
	int reserved0; // 2b
	 int section_length; // 12b
	 int transport_stream_id; // 16b
	 int reserved1; // 2b
	 int version_number; // 5b
	 int current_next_indicator; // 1b
	 int section_number; // 8b
	 int last_section_number; // 8b
	 int original_network_id; // 16b
	 int reserved_future_use2; // 8b
	 int nameListLen;
 	 sdtPrgName_st *nameList; // Commdes_st
	 int crc32; // 32b
}sdt_senction_st;

typedef struct Nit_streamLoop_st
{
	 int streamId;
	 int original_network_id;
	 BufferUn_st *BufferUn_stList; // Commdes_st//in fact is byte[]
	 int BufferUn_stLen;

}Nit_streamLoop_t;


typedef struct Nit_section_st
{
	int networkId;
	int version;
	Commdes_t *nameList; // Commdes_st
	int nameListLen;
	Nit_streamLoop_t *streamLoop; // Nit_streamLoop_st
	int streamLoopLen;
}Nit_section_t;

typedef struct cat_senction_t
{
	 int table_id; // 8b
	 int section_syntax_indicator; // 1b
	 int flag_0; // 1b
	 int reserved0; // 2b
	 int section_length; // 12b
	 int reserved1; // 18b
	 int reserved2; // 2b
	 int version_number; // 5b
	 int current_next_indicator; // 1b
	 int section_number; // 8b
	 int last_section_number; // 8b
	 CA_descriptor *caIdenList; // CA_descriptor
	 int caIdenListLen;
	 int crc32; // 32b
}cat_senction_st;

typedef struct replacePidt
{
	//internal byte inChannel;
	 int oldPid;
	 int newPid;
}replacePidst;


#pragma pack()

#endif	

