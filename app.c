// ===============================APP SANDBOX===============================
// These its a app server sandbox, dont make any kind of includes here

typedef void apprequest;
typedef void appresponse;
typedef int appbool;
#define app_true 1
#define app_false 0


typedef struct appdeps{

    int (*printf)(const char *format, ...);


    const apprequest *apprequest;
    const char *route;

    const char *(*get_headder)(const apprequest *apprequest, const char *key);
    const char *(*get_headder_key)(const apprequest *apprequest,int index);
    const char *(*get_headder_value)(const apprequest *apprequest,int index);


    const char *(*get_method)(const apprequest *apprequest); 
    const char *(*get_query_param)(const apprequest *apprequest, const char *key);
    const char *(*get_query_param_key)(const apprequest *apprequest,int index);
    const char *(*get_query_param_value)(const apprequest *apprequest,int index);
   
    const unsigned char *(*read_body)(const apprequest *apprequest, long size, long *readed_size);
    const appresponse *(*send_any)(const unsigned char *content,long content_size,const char *content_type, int status_code);
    const appresponse *(*send_file)(const char *path,const char *content_type, int status_code);






} appdeps;

appresponse * mainserver(appdeps *deps){
   
}