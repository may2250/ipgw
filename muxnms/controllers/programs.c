/*
    programs Controller for esp-html-mvc (esp-html-mvc)
 */
#include "esp.h"
#include "cJSON.h"

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

static void getPrgs() {

}


static void redirectPost() {
    redirect(sjoin(getConn()->rx->uri, "/", NULL));
}

static void common(HttpConn *conn) {
    cchar *role = getSessionVar("role");
    if(role == NULL){
        rendersts(str, 9);
        render(str);
        return;
    }
}

/*
    Dynamic module initialization
 */
ESP_EXPORT int esp_controller_ipgw_programs(HttpRoute *route, MprModule *module) {
    espDefineBase(route, common);
    espDefineAction(route, "programs-getPrgs", getPrgs);
    
#if SAMPLE_VALIDATIONS
    Edi *edi = espGetRouteDatabase(route);
    ediAddValidation(edi, "present", "programs", "title", 0);
    ediAddValidation(edi, "unique", "programs", "title", 0);
    ediAddValidation(edi, "banned", "programs", "body", "(swear|curse)");
    ediAddValidation(edi, "format", "programs", "phone", "/^\\(?([0-9]{3})\\)?[-. ]?([0-9]{3})[-. ]?([0-9]{4})$/");
#endif
    return 0;
}
