#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "datastructdef.h"
#include "list.h"
#include "communicate.h"
#include "cJSON.h"

ClsProgram_st clsProgram;

int main(int argc,char *argv[])
{
    char sendbuf[256];
    int len=0,i,ret=0;

    if(!argv[1]){
	    perror("please input ip\n");
	    return -1;
    }

    return 0;
}
