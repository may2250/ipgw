/*
    globalopt Controller for esp-html-mvc (esp-html-mvc)
 */
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "esp.h"
#include "devinfo.h"
#include "cJSON.h"
#include "datastructdef.h"
#include "list.h"

/*
    Create a new resource in the database
 */
char *tmpip = "192.168.1.49";
//conn->rx->parsedUri->host
char optstr[256] = {0};
extern ClsProgram_st clsProgram;

static void rendersts(const char *str,int status)
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

void substr(const char*str,unsigned start, unsigned end, char *stbuf)
{
   unsigned n = end - start;
   strncpy(stbuf, str + start, n);
   stbuf[n] = 0;
}

static void reboot(HttpConn *conn) {
    char str[16] = {0};
    cchar *role = getSessionVar("role");
    if(role == NULL){
        rendersts(str, 9);
        render(str);
        return;
    }
    if((strcmp(role, "root") !=0) && (strcmp(role, "admin") !=0)){
        rendersts(str, 5);//无权限设置Ip
        render(str);
        return;
    }

	rebootDevice(tmpip);
	rendersts(str, 1);
	render(str);
	//add optlog
    Edi *db = ediOpen("db/ipgw.mdb", "mdb", EDI_AUTO_SAVE);
    EdiRec *optlog = ediCreateRec(db, "optlog");
    if(optlog == NULL){
       printf("================>>>optlog is NULL!!\n");
       return;
    }
    time_t curTime;
    //struct tm *ts;
    time(&curTime);
    memset(optstr, 0, 256);
	cchar *lan = getSessionVar("language");
	if(!strcmp(lan, "zh-CN")){
		sprintf(optstr, "{'user': '%s', 'desc': '设备重启.', 'level': '2', 'logtime':'%d'}", getSessionVar("userName"), curTime);
	}else{
		sprintf(optstr, "{'user': '%s', 'desc': 'Device Reboot.', 'level': '2', 'logtime':'%d'}", getSessionVar("userName"), curTime);
	}
    
    MprJson  *row = mprParseJson(optstr);
    if(ediSetFields(optlog, row) == 0){
       printf("================>>>ediSetFields Failed!!\n");
    }
    ediUpdateRec(db, optlog);
    //ediClose(db);
}

static void reset(HttpConn *conn) {
    char str[16] = {0};
    cchar *role = getSessionVar("role");
    if(role == NULL){
        rendersts(str, 9);
        render(str);
        return;
    }
    if((strcmp(role, "root") !=0) && (strcmp(role, "admin") !=0)){
        rendersts(str, 5);//无权限
        render(str);
        return;
    }

	restoreFactory(tmpip);
	rendersts(str, 1);
	render(str);
	//add optlog
    Edi *db = ediOpen("db/ipgw.mdb", "mdb", EDI_AUTO_SAVE);
    EdiRec *optlog = ediCreateRec(db, "optlog");
    if(optlog == NULL){
       printf("================>>>optlog is NULL!!\n");
       return;
    }
    time_t curTime;
    time(&curTime);
    memset(optstr, 0, 256);
	cchar *lan = getSessionVar("language");
	if(!strcmp(lan, "zh-CN")){
		sprintf(optstr, "{'user': '%s', 'desc': '恢复出厂设置.', 'level': '2', 'logtime':'%d'}", getSessionVar("userName"), curTime);
	}else{
		sprintf(optstr, "{'user': '%s', 'desc': 'Restore Default.', 'level': '2', 'logtime':'%d'}", getSessionVar("userName"), curTime);
	}
    
    MprJson  *row = mprParseJson(optstr);
    if(ediSetFields(optlog, row) == 0){
       printf("================>>>ediSetFields Failed!!\n");
    }
    ediUpdateRec(db, optlog);
    //ediClose(db);
}

static void setDevip(HttpConn *conn) {
    char str[16] = {0};
    cchar *role = getSessionVar("role");
    if(role == NULL){
        rendersts(str, 9);
        render(str);
        return;
    }
    if((strcmp(role, "root") !=0) && (strcmp(role, "admin") !=0)){
        rendersts(str, 5);//无权限设置Ip
        render(str);
        return;
    }
	cchar *param = espGetQueryString(conn);

	char newip[16] = {0};
	char newgatway[16] = {0};
	char submask[16] = {0};
	char* ptr = strchr(param, '&');
    int pos = ptr-param;
	substr(param, 0, pos, newip);
	char *ptr1 = strrchr (param, '&');
	int flag = ptr1 - param;
	substr(param, pos + 1, flag, newgatway);
	substr(param, flag + 1, strlen(param), submask);
	unsigned int vip = ntohl( inet_addr( newip ) );
	unsigned int tmpgatway = ntohl( inet_addr( newgatway ) );
	unsigned int tmpsubmask = ntohl( inet_addr( submask ) );
	if(0 == setIp(tmpip, vip)){
		setGateway(tmpip, tmpgatway);
		getSubMask(tmpip, tmpsubmask);
	}
	rendersts(str, 1);
	render(str);
	//add optlog
    Edi *db = ediOpen("db/ipgw.mdb", "mdb", EDI_AUTO_SAVE);
    EdiRec *optlog = ediCreateRec(db, "optlog");
    if(optlog == NULL){
       printf("================>>>optlog is NULL!!\n");
       return;
    }
    time_t curTime;
    time(&curTime);
    memset(optstr, 0, 256);
	cchar *lan = getSessionVar("language");
	if(!strcmp(lan, "zh-CN")){
		sprintf(optstr, "{'user': '%s', 'desc': '设备修改IP【IP:%s】.', 'level': '2', 'logtime':'%d'}", getSessionVar("userName"),newip, curTime);
	}else{
		sprintf(optstr, "{'user': '%s', 'desc': 'Device change IP【IP:%s】.', 'level': '2', 'logtime':'%d'}", getSessionVar("userName"),newip, curTime);
	}
    
    MprJson  *row = mprParseJson(optstr);
    if(ediSetFields(optlog, row) == 0){
       printf("================>>>ediSetFields Failed!!\n");
    }
    ediUpdateRec(db, optlog);
    //ediClose(db);
}

static void setPassword(HttpConn *conn) {
    char str[16] = {0};
    cchar *role = getSessionVar("role");
    if(role == NULL){
        rendersts(str, 9);
        render(str);
        return;
    }
    if((strcmp(role, "root") !=0) && (strcmp(role, "admin") !=0)){
        rendersts(str, 5);//无权限
        render(str);
        return;
    }
    MprJson *jsonparam = mprParseJson(espGetQueryString(conn));
    cchar *oldpassword = mprGetJson(jsonparam, "oldpassword");
    cchar *newpassword = mprGetJson(jsonparam, "newpassword");

    cchar *username = getSessionVar("userName");
    //Edi *db = ediOpen("db/ipgw.mdb", "mdb", EDI_AUTO_SAVE );
    EdiRec *user = readRecWhere("user", "username", "==", username);
    MprJson *userjson = mprParseJson(ediRecAsJson(user, 0));
    //printf("=======password====%s========%s\n", oldpassword, mprGetJson(userjson, "password"));
    if(strcmp(oldpassword, mprGetJson(userjson, "password")) == 0){
        ediSetField(user, "password", newpassword);
        updateRec(user);
        rendersts(str, 1);
    }else{
        rendersts(str, 0);
    }
    //ediClose(db);
    render(str);
    //add optlog
    Edi *db = ediOpen("db/ipgw.mdb", "mdb", EDI_AUTO_SAVE);
    EdiRec *optlog = ediCreateRec(db, "optlog");
    if(optlog == NULL){
       printf("================>>>optlog is NULL!!\n");
       return;
    }
    time_t curTime;
    time(&curTime);
    memset(optstr, 0, 256);
	cchar *lan = getSessionVar("language");
	if(!strcmp(lan, "zh-CN")){
		sprintf(optstr, "{'user': '%s', 'desc': '用户修改了密码.', 'level': '2', 'logtime':'%d'}", getSessionVar("userName"), curTime);
	}else{
		sprintf(optstr, "{'user': '%s', 'desc': 'User changed password.', 'level': '2', 'logtime':'%d'}", getSessionVar("userName"), curTime);
	}
    
    MprJson  *row = mprParseJson(optstr);
    if(ediSetFields(optlog, row) == 0){
       printf("================>>>ediSetFields Failed!!\n");
    }
    ediUpdateRec(db, optlog);
    //ediClose(db);
}

static void getoptlogs() {
    char str[16] = {0};
    int len = 0;
    cchar *role = getSessionVar("role");
    if(role == NULL){
        rendersts(str, 9);
        render(str);
        return;
    }
    if((strcmp(role, "root") !=0) && (strcmp(role, "admin") !=0)){
        rendersts(str, 5);//无权限
        render(str);
        return;
    }
	//find optlog
    Edi *db = ediOpen("db/ipgw.mdb", "mdb", EDI_AUTO_SAVE);
//    //删除7天前的日志
    time_t curTime;
    time(&curTime);
    //EdiGrid *oldlogs = ediReadWhere(db, "optlog", "logtime", "<", curTime - 7*24*3600);
    EdiGrid *oldlogs = ediReadTable(db, "optlog");
    //printf("========logs========>>>%s\n", ediGridAsJson(oldlogs, MPR_JSON_PRETTY));
    for(len=0; len < oldlogs->nrecords; len++){
        EdiRec *log = oldlogs->records[len];
        if(atoi(mprGetJson(mprParseJson(ediRecAsJson(log, MPR_JSON_PRETTY)), "logtime")) < (curTime - 7*24*3600)){
            ediRemoveRec(db, "optlog", log->id);
        }
    }

    EdiGrid *logs = ediReadTable(db, "optlog");
    render(ediGridAsJson(logs, MPR_JSON_PRETTY));
}

static void common(HttpConn *conn) {
}

/*
    Dynamic module initialization
 */
ESP_EXPORT int esp_controller_ipgw_globalopt(HttpRoute *route, MprModule *module) {
    espDefineBase(route, common);
    espDefineAction(route, "globalopt-cmd-reboot", reboot);
	espDefineAction(route, "globalopt-cmd-reset", reset);
	espDefineAction(route, "globalopt-cmd-setDevip", setDevip);
	espDefineAction(route, "globalopt-cmd-setPassword", setPassword);
	espDefineAction(route, "globalopt-cmd-getoptlogs", getoptlogs);

#if SAMPLE_VALIDATIONS
    Edi *edi = espGetRouteDatabase(route);
    ediAddValidation(edi, "present", "globalopt", "title", 0);
    ediAddValidation(edi, "unique", "globalopt", "title", 0);
    ediAddValidation(edi, "banned", "globalopt", "body", "(swear|curse)");
    ediAddValidation(edi, "format", "globalopt", "phone", "/^\\(?([0-9]{3})\\)?[-. ]?([0-9]{3})[-. ]?([0-9]{4})$/");
#endif
    return 0;
}
