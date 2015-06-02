#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "communicate.h"

extern ClsProgram_st clsProgram;

private void RefreshIpInOutMode(char *ip)
{
    unsigned char[] buf[32] = {0};
    unsigned char[] sendbuf ={0x77,0x6c,0xf0,0x0, 0x1, 0x1};
    int slen=0, i = 0;
    communicate(ip, sendbuf, 5, buf, &slen);

    if(slen == sizeof(sendbuf) + 1){
        int mode = buf[6];
        if(mode == 1){
            clsProgram.ipGwDb->devNetFun = 1;
        }else{
            clsProgram.ipGwDb->devNetFun = 0;
        }
    }
}