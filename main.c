

#include "dependencies/doTheWorldOne.c"
#include "dependencies/CWebStudioOne.c"
#include "app.c"
// ===============================SERVER WRAPPERS===============================

const char *wrapper_get_route(const void *apprequest){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return request->route;
}
const char *wrapper_get_method(const void *apprequest){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return request->method;
}
//================================HEADDERS================================
const char *wrapper_get_headder(const void *apprequest, const char *key){
    return CwebHttpRequest_get_header((CwebHttpRequest *)apprequest, key);
}

const char *wrapper_get_headder_key(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->headers->size){
        return NULL;
    }
    CwebDict *headders = request->headers;
    CwebKeyVal *keyval = headders->keys_vals[index];
    return keyval->key;
}

const char *wrapper_get_headder_value(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->headers->size){
        return NULL;
    }
    CwebDict *headders = request->headers;
    CwebKeyVal *keyval = headders->keys_vals[index];
    return keyval->value;
}

//================================PARAMS================================
const char *wrapper_get_query_param(const void *apprequest, const char *key){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return CwebHttpRequest_get_param(request, key);
}

const char *wrapper_get_query_param_key(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->params->size){
        return NULL;
    }
    CwebDict *query_params = request->params;
    CwebKeyVal *keyval = query_params->keys_vals[index];
    return keyval->key;
}

const char *wrapper_get_query_param_value(const void *apprequest, int index){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    if(index < 0 || index >= request->params->size){
        return NULL;
    }
    CwebDict *query_params = request->params;
    CwebKeyVal *keyval = query_params->keys_vals[index];
    return keyval->value;
}

const unsigned char *wrapper_read_body(const void *apprequest, long size, long *readed_size){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    unsigned char *response_body = CwebHttpRequest_read_content(request, size);
    *readed_size = request->content_length;
    return (const unsigned char *)response_body;
}
const void *wrapper_read_json(const void *apprequest, long size){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    cJSON *json = CWebHttpRequest_read_cJSON(request, size);
    return (const void *)json;
}

//================================RESPONSE================================
const void  *wrapper_send_any(const unsigned char *content,long content_size,const char *content_type, int status_code){
    return (void *)cweb_send_any(content_type, content_size, (unsigned char *)content, status_code);
}
const void *wrapper_send_text(const char *text, int status_code){
    return (void *)cweb_send_text(text, status_code);
}
const void *wrapper_send_file(const char *path,const char *content_type, int status_code){
    return (void *)cweb_send_file(path, content_type, status_code);
}

// ===============================APP===============================

CwebHttpResponse *main_internal_server(CwebHttpRequest *request) {
    
    appdeps appdeps = {0};
    
    // Request data
  
    
    // Standard library functions
    appdeps.printf = printf;
    appdeps.sprintf = sprintf;
    appdeps.snprintf = snprintf;
    appdeps.strlen = strlen;
    appdeps.strcpy = strcpy;
    appdeps.atoi = atoi;
    appdeps.atof = atof;
    
    // HTTP request wrapper functions
    appdeps.apprequest = (const void*)request;
    appdeps.get_route = wrapper_get_route;
    appdeps.get_headder = wrapper_get_headder;
    appdeps.get_headder_key = wrapper_get_headder_key;
    appdeps.get_headder_value = wrapper_get_headder_value;
    appdeps.get_method = wrapper_get_method;
    appdeps.get_query_param = wrapper_get_query_param;
    appdeps.get_query_param_key = wrapper_get_query_param_key;
    appdeps.get_query_param_value = wrapper_get_query_param_value;
    appdeps.read_body = wrapper_read_body;
    
    // HTTP response wrapper functions
    appdeps.send_any = wrapper_send_any;
    appdeps.send_text = wrapper_send_text;
    appdeps.send_file = wrapper_send_file;

   const void *response = mainserver(&appdeps);
   return (CwebHttpResponse *)response;
}

int main(int argc, char *argv[]) {
    CwebServer server = newCwebSever(5000, main_internal_server);
    CwebServer_start(&server);
    return 0;
}
