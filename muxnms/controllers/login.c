/* 
    login Controller for esp-html-mvc (esp-html-mvc) 
 */  
#include "esp.h"
#include "cJSON.h"

static void checkLogin() {
    cchar *name = param("username");
    cchar *pwd = param("password");
    cJSON *result = cJSON_CreateObject();
    char* jsonstring;
    char str[16] = {0};
    char optstr[256] = {0};
    Edi *db = ediOpen("db/muxnms.mdb", "mdb", EDI_AUTO_SAVE);

	//读取用户认证信息
	EdiRec *user = readRecWhere("user", "username", "==", name);
	if(user == NULL){
	    cJSON_AddNumberToObject(result,"sts", 1);
        jsonstring = cJSON_PrintUnformatted(result);
        memcpy(str, jsonstring, strlen(jsonstring));
	    render(jsonstring);
	    //释放内存
        cJSON_Delete(result);
        free(jsonstring);
	    return;
	}
	MprJson *userjson = mprParseJson(ediRecAsJson(user, 0));

    if(strcmp(mprGetJson(userjson, "password"),pwd) == 0 )
    {
        setSessionVar("isAuthed", "true");
        setSessionVar("userName", name);
        setSessionVar("role", mprGetJson(userjson, "roles"));
        cJSON_AddNumberToObject(result,"sts", 0);
        jsonstring = cJSON_PrintUnformatted(result);
        memcpy(str, jsonstring, strlen(jsonstring));
        render(jsonstring);
        //释放内存
        cJSON_Delete(result);
        free(jsonstring);
        //add optlog
         EdiRec *optlog = ediCreateRec(db, "optlog");
         if(optlog == NULL){
            printf("================>>>optlog is NULL!!\n");
         }

         time_t curTime;
         //struct tm *ts;
         time(&curTime);
         //ts = localtime(&curTime);
         sprintf(optstr, "{'user': '%s', 'desc': '用户登录', 'level': '1', 'logtime':'%d'}", name, curTime);
         MprJson  *row = mprParseJson(optstr);
         if(ediSetFields(optlog, row) == 0){
            printf("================>>>ediSetFields Failed!!\n");
         }
         ediUpdateRec(db, optlog);
         //ediClose(db);

    }else{
		cJSON_AddNumberToObject(result,"sts", 2);
        jsonstring = cJSON_PrintUnformatted(result);
        memcpy(str, jsonstring, strlen(jsonstring));
        render(jsonstring);
        //释放内存
        cJSON_Delete(result);
        free(jsonstring);
    }        
}  

static void checkLoginOut() {  
	setSessionVar("isAuthed", "false");
	render("OK");
}  

static void common(HttpConn *conn) {  
}  
  
/* 
    Dynamic module initialization 
 */  
ESP_EXPORT int esp_controller_muxnms_login(HttpRoute *route, MprModule *module) {  
    espDefineBase(route, common);  
    espDefineAction(route, "login-cmd-check", checkLogin);  
	espDefineAction(route, "login-cmd-logout", checkLoginOut); 
    return 0;  
}  