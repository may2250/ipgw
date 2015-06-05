


#ifndef _DEV_INFO_H_
#define _DEV_INFO_H_

int getDeviceType(char *ip,  unsigned int  *outType);
int getHardVersion(char *ip,  unsigned int  *outHardVer);
int getSoftVersion(char *ip,  unsigned int  *outSoftVer);
int getFpgaVersion(char *ip,  unsigned int  *outFPGAVer);
void rebootDevice(char *ip);
void restoreFactory(char *ip);
int getIp(char *ip,  unsigned int  *outIP);
int setIp(char *ip,  unsigned int  devip);
int getSubMask(char *ip,  unsigned int  *getSubMask);
int setSubMask(char *ip,  unsigned int  inSubMask);
int getGateway(char *ip,  unsigned int  *outGateway);
int setGateway(char *ip,  unsigned int  inGateway);
int getMac(char *ip,  unsigned char  *outMac, unsigned int outlen);
int setMac(char *ip,  unsigned char  *outMac);
int getPort(char *ip,  unsigned int  *outPort);
int setPort(char *ip,  unsigned int  port);

#endif
