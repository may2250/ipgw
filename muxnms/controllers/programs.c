/*
    programs Controller for esp-html-mvc (esp-html-mvc)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "esp.h"
#include "cJSON.h"
#include "ipgw.h"
#include "getJsonstr.h"
#include "clsMuxprgInfoGet.h"

char *tmpip = "192.168.1.49";

extern ClsProgram_st clsProgram;

static void rendersts(char *str,int status)
{
	cJSON *result = cJSON_CreateObject();
	char* jsonstring;
	cJSON_AddNumberToObject(result,"sts", status);
	jsonstring = cJSON_PrintUnformatted(result);
	memcpy(str, jsonstring, strlen(jsonstring));
	//释放内存
	cJSON_Delete(result);
	free(jsonstring);
}

static int isAuthed(){
    char str[32] = {0};
    cchar *isAuthed = getSessionVar("isAuthed");
    if(isAuthed == NULL){
        rendersts(str, 8);
        render(str);
        return 1;
    }
    if(strcmp(isAuthed, "false") == 0){
        rendersts(str, 8);
        render(str);
        return 1;
    }
    return 0;
}

static void getDevinfo(HttpConn *conn) {
    if(isAuthed()){
        return;
    }
    char pProg[256] = {0};
    int r = 0;
    EdiField *src;
    printf("---------------getdevinfo===\n");
    getbaseJson(tmpip, pProg);
    printf("---------------getdevinfo end===\n");
    render(pProg);
    //delete optlog 7days ago
    Edi *db = ediOpen("db/muxnms.mdb", "mdb", EDI_AUTO_SAVE);
    time_t curTime;
    time(&curTime);
    EdiGrid *opts = ediReadTable(db, "optlog");
    if(opts != NULL){
       for (r = 0; r < opts->nrecords; r++) {
           src = opts->records[r]->fields;
           src += 4;
           if(atoi(src->value) < (curTime - 7*24*3600)){
                ediRemoveRec(db, "optlog", opts->records[r]->id);
           }
       }
    }
}

static void search(HttpConn *conn) {
    if(isAuthed()){
        return;
    }
    char str[32] = {0};
    RefreshIpInOutMode(tmpip);
    if(clsProgram.ipGwDb->devNetFun == 0){
        if(Search(tmpip, 1)){
            //error
            rendersts(str, 6);
            render(str);
            return;
        }
    }
    rendersts(str, 1);
    render(str);
}

static void getPrgs(HttpConn *conn) {
    if(isAuthed()){
        return;
    }
    char outprg[102400] = {0};
    getPrgsJson(tmpip, outprg);
    render(outprg);
}

static void ipRead(HttpConn *conn) {
    if(isAuthed()){
        return;
    }
    char outprg[128] = {0};
    if(getIpReadJson(tmpip, outprg)){
        rendersts(outprg, 8);
        render(outprg);
        return;
    }
    render(outprg);
}

//
//cchar *role = getSessionVar("role");
//if(role == NULL){
//    rendersts(str, 9);
//    render(str);
//    return;
//}
// if((strcmp(role, "root") !=0) && (strcmp(role, "admin") !=0)){
//    rendersts(str, 5);//无权限
//    render(str);
//    return;
//}

//
//static void redirectPost() {
//    redirect(sjoin(getConn()->rx->uri, "/", NULL));
//}



static void common(HttpConn *conn) {

}

static void espinit() {
	ChannelProgramSt *pst = NULL;
	//全局变量初始化
	clsProgram._outChannelCntMax = 1;
	clsProgram._intChannelCntMax = 8;
	clsProgram._pmtMaxCnt = 29;
	clsProgram.prgNum_min = 1;
	clsProgram.prgPid_min = 0x100;
	clsProgram.prgPid_max = 0xfff;
	//给全局变量申请内存
    pst = malloc(sizeof(ChannelProgramSt));
    memset(pst, 0, sizeof(ChannelProgramSt));
    pst->channelId = 1;
    list_append(&(clsProgram.inPrgList), pst);

    Init();
	printf("======>>>>esp init!!!!!!!\n");
}

/*
    Dynamic module initialization
 */
ESP_EXPORT int esp_controller_ipgw_programs(HttpRoute *route, MprModule *module) {
    espDefineBase(route, common);
    espinit();
    espDefineAction(route, "programs-cmd-getDevinfo", getDevinfo);
    espDefineAction(route, "programs-cmd-ipRead", ipRead);
    espDefineAction(route, "programs-cmd-getPrgs", getPrgs);
    espDefineAction(route, "programs-cmd-search", search);
    
#if SAMPLE_VALIDATIONS
    Edi *edi = espGetRouteDatabase(route);
    ediAddValidation(edi, "present", "programs", "title", 0);
    ediAddValidation(edi, "unique", "programs", "title", 0);
    ediAddValidation(edi, "banned", "programs", "body", "(swear|curse)");
    ediAddValidation(edi, "format", "programs", "phone", "/^\\(?([0-9]{3})\\)?[-. ]?([0-9]{3})[-. ]?([0-9]{4})$/");
#endif
    return 0;
}
