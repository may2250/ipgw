#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "datastructdef.h"

int main(int argc,char *argv[])
{
    if(!argv[1]){
	    perror("please input ip\n");
	    return -1;
    }

    return 0;
}
