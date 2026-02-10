#include "app.c"


#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#endif 


#include "dependencies/doTheWorld.h"
#include "dependencies/BearHttpsClient.h"

#include "dependencies/CWebStudio.h"
#include "dependencies/CArgvParse.h"
#include "assets.h"




// ===============================STD WRAPPERS==================================

int wrapper_snprintf(char *str, unsigned long size, const char *format, ...){
    va_list args;
    va_start(args, format);
    int result = vsnprintf(str, (size_t)size, format, args);
    va_end(args);
    return result;
}

unsigned long wrapper_strlen(const char *s){
    return (unsigned long)strlen(s);
}

void *wrapper_malloc(unsigned long size){
    return malloc((size_t)size);
}

void *wrapper_calloc(unsigned long num, unsigned long size){
    return calloc((size_t)num, (size_t)size);
}

void *wrapper_realloc(void *ptr, unsigned long size){
    return realloc(ptr, (size_t)size);
}

// ===============================SERVER WRAPPERS===============================

const char *wrapper_get_server_route(const void *apprequest){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return request->route;
}
const char *wrapper_get_server_method(const void *apprequest){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return request->method;
}
//================================HEADDERS================================
const char *wrapper_get_server_headder(const void *apprequest, const char *key){
    return CwebHttpRequest_get_header((CwebHttpRequest *)apprequest, key);
}

const char *wrapper_get_server_headder_key(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->headers->size){
        return NULL;
    }
    CwebDict *headders = request->headers;
    CwebKeyVal *keyval = headders->keys_vals[index];
    return keyval->key;
}

const char *wrapper_get_server_headder_value(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->headers->size){
        return NULL;
    }
    CwebDict *headders = request->headers;
    CwebKeyVal *keyval = headders->keys_vals[index];
    return keyval->value;
}

//================================PARAMS================================
const char *wrapper_get_server_query_param(const void *apprequest, const char *key){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return CwebHttpRequest_get_param(request, key);
}

const char *wrapper_get_server_query_param_key(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->params->size){
        return NULL;
    }
    CwebDict *query_params = request->params;
    CwebKeyVal *keyval = query_params->keys_vals[index];
    return keyval->key;
}

const char *wrapper_get_server_query_param_value(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->params->size){
        return NULL;
    }
    CwebDict *query_params = request->params;
    CwebKeyVal *keyval = query_params->keys_vals[index];
    return keyval->value;
}

const unsigned char *wrapper_read_server_body(const void *apprequest, long size, long *readed_size){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    unsigned char *response_body = CwebHttpRequest_read_content(request, size);
    *readed_size = request->content_length;
    return (const unsigned char *)response_body;
}
const void *wrapper_read_server_json(const void *apprequest, long size){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    cJSON *json = CWebHttpRequest_read_cJSON(request, size);
    return (const void *)json;
}
//================================JSON PARSING================================
void *wrapper_json_parse(const char *value){
    return (void *)cJSON_Parse(value);
}

void *wrapper_json_parse_file(const char *filepath){
    char *content = dtw_load_string_file_content(filepath);
    if(content == NULL) return NULL;
    cJSON *json = cJSON_Parse(content);
    free(content);
    return (void *)json;
}

void wrapper_json_delete(void *json){
    cJSON_Delete((cJSON *)json);
}

//================================JSON SERIALIZATION================================
char *wrapper_json_print(const void *json){
    return cJSON_Print((cJSON *)json);
}

char *wrapper_json_print_unformatted(const void *json){
    return cJSON_PrintUnformatted((cJSON *)json);
}

int wrapper_json_save_file(const void *json, const char *filepath){
    char *content = cJSON_Print((cJSON *)json);
    if(content == NULL) return 0;
    dtw_write_string_file_content(filepath, content);
    cJSON_free(content);
    return 1;
}

void wrapper_json_free_string(char *str){
    cJSON_free(str);
}

//================================JSON CREATION================================
void *wrapper_json_create_object(void){
    return (void *)cJSON_CreateObject();
}

void *wrapper_json_create_array(void){
    return (void *)cJSON_CreateArray();
}

void *wrapper_json_create_string(const char *string){
    return (void *)cJSON_CreateString(string);
}

void *wrapper_json_create_number(double num){
    return (void *)cJSON_CreateNumber(num);
}

void *wrapper_json_create_bool(int boolean){
    return (void *)cJSON_CreateBool(boolean);
}

void *wrapper_json_create_null(void){
    return (void *)cJSON_CreateNull();
}

void *wrapper_json_duplicate(const void *item, int recurse){
    return (void *)cJSON_Duplicate((cJSON *)item, recurse);
}

//================================JSON OBJECT MANIPULATION================================
void *wrapper_json_get_object_item(const void *object, const char *key){
    return (void *)cJSON_GetObjectItem((cJSON *)object, key);
}

int wrapper_json_has_object_item(const void *object, const char *key){
    return cJSON_HasObjectItem((cJSON *)object, key);
}

int wrapper_json_add_item_to_object(void *object, const char *key, void *item){
    return cJSON_AddItemToObject((cJSON *)object, key, (cJSON *)item);
}

int wrapper_json_delete_item_from_object(void *object, const char *key){
    cJSON_DeleteItemFromObject((cJSON *)object, key);
    return 1;
}

int wrapper_json_replace_item_in_object(void *object, const char *key, void *newitem){
    return cJSON_ReplaceItemInObject((cJSON *)object, key, (cJSON *)newitem);
}

void *wrapper_json_add_string_to_object(void *object, const char *key, const char *string){
    return (void *)cJSON_AddStringToObject((cJSON *)object, key, string);
}

void *wrapper_json_add_number_to_object(void *object, const char *key, double number){
    return (void *)cJSON_AddNumberToObject((cJSON *)object, key, number);
}

void *wrapper_json_add_bool_to_object(void *object, const char *key, int boolean){
    return (void *)cJSON_AddBoolToObject((cJSON *)object, key, boolean);
}

void *wrapper_json_add_null_to_object(void *object, const char *key){
    return (void *)cJSON_AddNullToObject((cJSON *)object, key);
}

void *wrapper_json_add_object_to_object(void *object, const char *key){
    return (void *)cJSON_AddObjectToObject((cJSON *)object, key);
}

void *wrapper_json_add_array_to_object(void *object, const char *key){
    return (void *)cJSON_AddArrayToObject((cJSON *)object, key);
}

//================================JSON ARRAY MANIPULATION================================
int wrapper_json_get_array_size(const void *array){
    return cJSON_GetArraySize((cJSON *)array);
}

void *wrapper_json_get_array_item(const void *array, int index){
    return (void *)cJSON_GetArrayItem((cJSON *)array, index);
}

int wrapper_json_add_item_to_array(void *array, void *item){
    return cJSON_AddItemToArray((cJSON *)array, (cJSON *)item);
}

int wrapper_json_insert_item_in_array(void *array, int index, void *item){
    return cJSON_InsertItemInArray((cJSON *)array, index, (cJSON *)item);
}

int wrapper_json_replace_item_in_array(void *array, int index, void *newitem){
    return cJSON_ReplaceItemInArray((cJSON *)array, index, (cJSON *)newitem);
}

void wrapper_json_delete_item_from_array(void *array, int index){
    cJSON_DeleteItemFromArray((cJSON *)array, index);
}

//================================JSON TYPE CHECKING================================
int wrapper_json_is_object(const void *item){
    return cJSON_IsObject((cJSON *)item);
}

int wrapper_json_is_array(const void *item){
    return cJSON_IsArray((cJSON *)item);
}

int wrapper_json_is_string(const void *item){
    return cJSON_IsString((cJSON *)item);
}

int wrapper_json_is_number(const void *item){
    return cJSON_IsNumber((cJSON *)item);
}

int wrapper_json_is_bool(const void *item){
    return cJSON_IsBool((cJSON *)item);
}

int wrapper_json_is_null(const void *item){
    return cJSON_IsNull((cJSON *)item);
}

int wrapper_json_is_true(const void *item){
    return cJSON_IsTrue((cJSON *)item);
}

int wrapper_json_is_false(const void *item){
    return cJSON_IsFalse((cJSON *)item);
}

//================================JSON VALUE GETTERS================================
char *wrapper_json_get_string_value(const void *item){
    return cJSON_GetStringValue((cJSON *)item);
}

double wrapper_json_get_number_value(const void *item){
    return cJSON_GetNumberValue((cJSON *)item);
}

//================================JSON COMPARISON================================
int wrapper_json_compare(const void *a, const void *b, int case_sensitive){
    return cJSON_Compare((cJSON *)a, (cJSON *)b, case_sensitive);
}

//================================RESPONSE================================

const void *wrapper_newappserverresponse(){
    return (void*)newCwebHttpResponse();
}

void wrapper_setappserverresponse_headder(void  *appserverresponse, const char *key, const char *value){
    CwebHttpResponse_add_header((CwebHttpResponse *)appserverresponse, key, value);
}

void wrapper_setappserverresponse_content(void *appserverresponse, const unsigned char *content, long content_size){
    CwebHttpResponse_set_content((CwebHttpResponse *)appserverresponse, (unsigned char *)content, content_size);
}

void wrapper_setappserverresponse_status_code(void*appserverresponse, int status_code){
    ((CwebHttpResponse *)appserverresponse)->status_code = status_code;
}


const void  *wrapper_send_any(const unsigned char *content,long content_size,const char *content_type, int status_code){
    return (void *)cweb_send_any(content_type, content_size, (unsigned char *)content, status_code);
}
const void *wrapper_send_text(const char *text,const char *content_type, int status_code){
    return (void *)cweb_send_any(content_type, strlen(text), (unsigned char *)text, status_code);
}
const void *wrapper_send_file(const char *path,const char *content_type, int status_code){
    return (void *)cweb_send_file(path, content_type, status_code);
}
const void *wrapper_send_json(const void *json, int status_code){
    return cweb_send_cJSON((cJSON *)json, status_code);
}
//================================IO FUNCTIONS================================

unsigned char *wrapper_read_any(const char *path, long *size, int *is_binary){
    return dtw_load_any_content(path, size, (bool *)is_binary);
}
char *wrapper_read_string(const char *path){
    return dtw_load_string_file_content(path);
}
void wrapper_write_any(const char *path, const unsigned char *content, long size){
    dtw_write_any_content(path, (unsigned char *)content, size);
}

void wrapper_write_string(const char *path, const char *content){
    dtw_write_string_file_content(path, content);
}
void wrapper_delete_any(const char *path){
    dtw_remove_any(path);
}
void wrapper_create_dir(const char *path){
    dtw_create_dir_recursively(path);
}

int wrapper_file_exists(const char *path){
    return dtw_entity_type(path) == DTW_FILE_TYPE;
}
int wrapper_dir_exists(const char *path){
    return dtw_entity_type(path) == DTW_FOLDER_TYPE;
}

void wrapper_delete_stringarray(void *array){
    DtwStringArray_free((DtwStringArray *)array);
}
long wrapper_get_stringarray_size(void *array){
    return ((DtwStringArray *)array)->size;
}
const char *wrapper_get_stringarray_item(void *array, int index){
    return ((DtwStringArray *)array)->strings[index];
}

void *wrapper_list_files(const char *path){
    DtwStringArray *files = dtw_list_files(path,false);
    return (void *)files;
}
void *wrapper_list_dirs(const char *path){
    DtwStringArray *dirs = dtw_list_dirs(path,false);
    return (void *)dirs;
}
void *wrapper_list_any(const char *path){
    DtwStringArray *all = dtw_list_all(path,false);
    return (void *)all;
}
void *wrapper_list_files_recursively(const char *path){
    DtwStringArray *files = dtw_list_files_recursively(path,false);
    return (void *)files;
}
void *wrapper_list_dirs_recursively(const char *path){
    DtwStringArray *dirs = dtw_list_dirs_recursively(path,false);
    return (void *)dirs;
}
void *wrapper_list_any_recursively(const char *path){
    DtwStringArray *all = dtw_list_all_recursively(path,false);
    return (void *)all;
}

//================================ARGV PARSER FUNCTIONS================================
const char *wrapper_get_arg_value(const void *argv,int index){
    return CArgvParse_get_arg((CArgvParse *)argv,index);
}
int wrapper_get_arg_count(const void *argv){
    return ((CArgvParse *)argv)->total_args;
}

const char *wrapper_get_arg_flag_value(const void *argv,const char **flags,int total_flags,int index){
    return CArgvParse_get_flag((CArgvParse *)argv,flags,total_flags,index);
}

int wrapper_get_arg_flag_count(const void *argv,const char **flags,int total_flags){
    return CArgvParse_get_flag_size((CArgvParse *)argv,flags,total_flags);
}

appbool wrapper_has_arg_flag(const void *argv,const char **flags,int total_flags){
    return CArgvParse_is_flags_present((CArgvParse *)argv,flags,total_flags);
}
void *wrapper_newhttpclient(const char *url){
 BearHttpsRequest *request = newBearHttpsRequest(url);
 return (void*)request;
}
void wrapper_httpclient_set_method(void *client,const char *method){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    BearHttpsRequest_set_method(request, method);
}
void wrapper_httpclient_set_max_redirections(void *client,int max_redirections){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    request->max_redirections = max_redirections;
}
void * wrapper_httpclient_fetch(void *client){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    return (void *)BearHttpsRequest_fetch(request);
}
int wrapper_httpclient_response_get_status_code(void *response){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return resp->status_code;
}

unsigned char * wrapper_httpclient_response_read_body(void *response,long *size){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    unsigned char *body = (unsigned char *)BearHttpsResponse_read_body(resp);
    *size = resp->body_size;
    return body;
}
long wrapper_httpclient_response_get_body_size(void *response){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return resp->body_size;
}

int wrapper_httpclient_response_get_header_size(void *response){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return resp->headers->size;
}
void wrapper_httpclient_set_headder(void *client, const char *key, const char *value){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    BearHttpsRequest_add_header(request, key, value);
}
void wrapper_httpclient_set_body(void *client, unsigned char *content, long size){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    BearHttpsRequest_send_any(request, content, size);
}
void wrapper_httpclient_free(void *client){
    BearHttpsRequest *request = (BearHttpsRequest *)client;
    BearHttpsRequest_free(request);
}

char *wrapper_httpclient_response_get_headder_value_by_key(void *response, const char *key){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return (char *)BearHttpsResponse_get_header_value_by_key(resp, key);
}
const char *wrapper_httpclient_response_get_headder_key_by_index(void *response, int index){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return BearHttpsResponse_get_header_key_by_index(resp, index);
}
const char *wrapper_httpclient_response_get_headder_value_by_index(void *response, int index){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    return BearHttpsResponse_get_header_value_by_index(resp, index);
}

void wrapper_httpclient_response_free(void *response){
    BearHttpsResponse *resp = (BearHttpsResponse *)response;
    BearHttpsResponse_free(resp);
}
const unsigned char *wrapper_get_asset_content(const char *path,long *size,int *is_binary){
    for(int i=0; i < embedded_assets_total_size; i++){
        if(strcmp(embedded_assets[i].path, path) == 0){
            *size = embedded_assets[i].size;
            *is_binary = embedded_assets[i].is_binary;
            return embedded_assets[i].content;
        }
    }
    return NULL;
 
}
void *wrapper_list_assets(const char *path){
    DtwStringArray *array = newDtwStringArray();
    for(int i=0; i < embedded_assets_total_size; i++){
        if(dtw_starts_with(embedded_assets[i].path, path)){
            DtwStringArray_append(array, embedded_assets[i].path);
        }
    }
    return (void *)array;
  
}

// ===============================GLOBALS======================================
CArgvParse global_argv = {0};
appstart global_start_config ={0};
appdeps global_appdeps = {
    // Standard library functions
    .printf = printf,
    .sprintf = sprintf,
    .snprintf = wrapper_snprintf,
    .strlen = wrapper_strlen,
    .strcpy = strcpy,
    .atoi = atoi,
    .atof = atof,
    .free = free,
    .malloc = wrapper_malloc,
    .calloc = wrapper_calloc,
    .realloc = wrapper_realloc,
    
    // HTTP request wrapper functions
    .get_server_route = wrapper_get_server_route,
    .get_server_headder = wrapper_get_server_headder,
    .get_server_headder_key = wrapper_get_server_headder_key,
    .get_server_headder_value = wrapper_get_server_headder_value,
    .get_server_method = wrapper_get_server_method,
    .get_server_query_param = wrapper_get_server_query_param,
    .get_server_query_param_key = wrapper_get_server_query_param_key,
    .get_server_query_param_value = wrapper_get_server_query_param_value,
    .read_server_body = wrapper_read_server_body,
    .read_server_json = wrapper_read_server_json,

    // HTTP response wrapper functions
    .newappserverresponse = wrapper_newappserverresponse,
    .setappserverresponse_headder = wrapper_setappserverresponse_headder,
    .setappserverresponse_content = wrapper_setappserverresponse_content,
    .setappserverresponse_status_code = wrapper_setappserverresponse_status_code,
    .send_any = wrapper_send_any,
    .send_text = wrapper_send_text,
    .send_file = wrapper_send_file,
    .send_json = wrapper_send_json,

    // JSON parsing functions
    .json_parse = wrapper_json_parse,
    .json_parse_file = wrapper_json_parse_file,
    .json_delete = wrapper_json_delete,

    // JSON serialization functions
    .json_print = wrapper_json_print,
    .json_print_unformatted = wrapper_json_print_unformatted,
    .json_save_file = wrapper_json_save_file,
    .json_free_string = wrapper_json_free_string,

    // JSON creation functions
    .json_create_object = wrapper_json_create_object,
    .json_create_array = wrapper_json_create_array,
    .json_create_string = wrapper_json_create_string,
    .json_create_number = wrapper_json_create_number,
    .json_create_bool = wrapper_json_create_bool,
    .json_create_null = wrapper_json_create_null,
    .json_duplicate = wrapper_json_duplicate,

    // JSON object manipulation functions
    .json_get_object_item = wrapper_json_get_object_item,
    .json_has_object_item = wrapper_json_has_object_item,
    .json_add_item_to_object = wrapper_json_add_item_to_object,
    .json_delete_item_from_object = wrapper_json_delete_item_from_object,
    .json_replace_item_in_object = wrapper_json_replace_item_in_object,
    .json_add_string_to_object = wrapper_json_add_string_to_object,
    .json_add_number_to_object = wrapper_json_add_number_to_object,
    .json_add_bool_to_object = wrapper_json_add_bool_to_object,
    .json_add_null_to_object = wrapper_json_add_null_to_object,
    .json_add_object_to_object = wrapper_json_add_object_to_object,
    .json_add_array_to_object = wrapper_json_add_array_to_object,

    // JSON array manipulation functions
    .json_get_array_size = wrapper_json_get_array_size,
    .json_get_array_item = wrapper_json_get_array_item,
    .json_add_item_to_array = wrapper_json_add_item_to_array,
    .json_insert_item_in_array = wrapper_json_insert_item_in_array,
    .json_replace_item_in_array = wrapper_json_replace_item_in_array,
    .json_delete_item_from_array = wrapper_json_delete_item_from_array,

    // JSON type checking functions
    .json_is_object = wrapper_json_is_object,
    .json_is_array = wrapper_json_is_array,
    .json_is_string = wrapper_json_is_string,
    .json_is_number = wrapper_json_is_number,
    .json_is_bool = wrapper_json_is_bool,
    .json_is_null = wrapper_json_is_null,
    .json_is_true = wrapper_json_is_true,
    .json_is_false = wrapper_json_is_false,

    // JSON value getters
    .json_get_string_value = wrapper_json_get_string_value,
    .json_get_number_value = wrapper_json_get_number_value,

    // JSON comparison
    .json_compare = wrapper_json_compare,
    
    // IO functions
    .file_exists = wrapper_file_exists,
    .dir_exists = wrapper_dir_exists,
    .read_any = wrapper_read_any,
    .read_string = wrapper_read_string,
    .write_any = wrapper_write_any,
    .write_string = wrapper_write_string,
    .delete_any = wrapper_delete_any,
    .create_dir = wrapper_create_dir,

    // String array manipulation functions
    .delete_stringarray = wrapper_delete_stringarray,
    .get_stringarray_size = wrapper_get_stringarray_size,
    .get_stringarray_item = wrapper_get_stringarray_item,

    // List functions
    .list_files = wrapper_list_files,
    .list_dirs = wrapper_list_dirs,
    .list_any = wrapper_list_any,
    .list_files_recursively = wrapper_list_files_recursively,
    .list_dirs_recursively = wrapper_list_dirs_recursively,
    .list_any_recursively = wrapper_list_any_recursively,

    // ArgvParse functions
    .get_arg_value = wrapper_get_arg_value,
    .get_arg_count = wrapper_get_arg_count,
    .get_arg_flag_value = wrapper_get_arg_flag_value,
    .get_arg_flag_count = wrapper_get_arg_flag_count,
    .has_arg_flag = wrapper_has_arg_flag,

    // HTTP client functions
    .newappclientrequest = wrapper_newhttpclient,
    .appclientrequest_set_headder = wrapper_httpclient_set_headder,
    .appclientrequest_set_method = wrapper_httpclient_set_method,
    .appclientrequest_set_max_redirections = wrapper_httpclient_set_max_redirections,
    .appclientrequest_set_body = wrapper_httpclient_set_body,
    .appclientrequest_free = wrapper_httpclient_free,
    .appclientrequest_fetch = wrapper_httpclient_fetch,
    .appclientresponse_read_body = wrapper_httpclient_response_read_body,
    .appclientresponse_get_body_size = wrapper_httpclient_response_get_body_size,
    .appclientresponse_get_headder_value_by_key = wrapper_httpclient_response_get_headder_value_by_key,
    .appclientresponse_get_headder_key_by_index = wrapper_httpclient_response_get_headder_key_by_index,
    .appclientresponse_get_headder_value_by_index = wrapper_httpclient_response_get_headder_value_by_index,
    .appclientresponse_get_headder_size = wrapper_httpclient_response_get_header_size,
    .free_clientresponse = wrapper_httpclient_response_free,
    .get_asset_content = wrapper_get_asset_content,
    .list_assets = wrapper_list_assets
};
CwebHttpResponse *main_internal_server(CwebHttpRequest *request) {
    global_appdeps.appserverrequest = (const void*)request;
    const void *response = global_start_config.mainserver(&global_appdeps,global_start_config.props);
    return (CwebHttpResponse *)response;
}

CwebHttpResponse *main_internal_server_firmware(CwebHttpRequest *request,int argc,char *argv[]) {
    global_appdeps.appserverrequest = (const void*)request;
    global_argv = newCArgvParse(argc,argv);
    global_appdeps.argv = &global_argv;
    global_start_config = public_appstart(&global_appdeps);
    if(!global_start_config.start_server){
        return NULL;
    }

    const void *response = global_start_config.mainserver(&global_appdeps,global_start_config.props);
    if(global_start_config.free_props){
        global_start_config.free_props(global_start_config.props);
    }
    return (CwebHttpResponse *)response;
}

int main(int argc, char *argv[]) {
    global_argv = newCArgvParse(argc,argv);
    global_appdeps.argv = &global_argv;
    global_start_config = public_appstart(&global_appdeps);
    if(global_start_config.start_server){
        CwebServer server = newCwebSever(global_start_config.port, main_internal_server);
        server.use_static = false;
        #if !defined(_WIN32) && !defined(_WIN64)
            server.single_process =   global_start_config.single_process;
        #endif
        CwebServer_start(&server);
    }
    if(global_start_config.free_props){
        global_start_config.free_props(global_start_config.props);
    }
    return global_start_config.exit_code;
}
#include "assets.c"
#include "dependencies/BearHttpsClientOne.c"
#include "dependencies/CArgvParseOne.c"
#include "dependencies/CWebStudioOne.c"
#include "dependencies/doTheWorldOne.c"