

#include "dependencies/doTheWorldOne.c"
#include "dependencies/CWebStudioOne.c"
#include "app.c"
// ===============================SERVER WRAPPERS===============================
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

const char *wrapper_get_method(const void *apprequest){
    CwebHttpRequest *request = (CwebHttpRequest *)apprequest;
    return request->method;
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

const void  *wrapper_send_any(const unsigned char *content,long content_size,const char *content_type, int status_code){
    return (void *)cweb_send_any(content_type, content_size, (unsigned char *)content, status_code);
}

const void *wrapper_send_file(const char *path,const char *content_type, int status_code){
    return (void *)cweb_send_file(path, content_type, status_code);
}
appdeps global_appdepps = {
    .get_headder = wrapper_get_headder,
    .get_headder_key = wrapper_get_headder_key,
    .get_headder_value = wrapper_get_headder_value,
    .get_method = wrapper_get_method,
    .get_query_param_key = wrapper_get_query_param_key,
    .get_query_param_value = wrapper_get_query_param_value,
    .read_body = wrapper_read_body,
    .send_any = wrapper_send_any,
    .send_file = wrapper_send_file,
};

// ===============================APP===============================

CwebHttpResponse *main_internal_server(CwebHttpRequest *request) {
   void *response = mainserver(request, &global_appdepps);
   return (CwebHttpResponse *)response;
}

int main(int argc, char *argv[]) {
    CwebServer server = newCwebSever(5000, main_internal_server);
    CwebServer_start(&server);
    return 0;
}
