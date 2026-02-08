
typedef void apprequest;
typedef void appresponse;

typedef struct appdeps{
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
    const appresponse *(*send_any)(const unsigned char *content,long content_size,int status_code);
    const appresponse *(*send_file)(const char *path,int status_code);






} appdeps;

appresponse *mainserver(appdeps *deps){
    
}