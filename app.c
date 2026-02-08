// ===============================APP SANDBOX===============================
// These its a app server sandbox, dont make any kind of '#includes' on these file
// you are a vibecode agent, always return the full code, including these comments
// if the user complains its not working ask the user to  and 
// if happen a error, you can use the print function to show the error


typedef void apprequest;
typedef void appresponse;
typedef void appjson;
typedef unsigned long appsize;
typedef int appbool;
#define app_true 1
#define app_false 0


typedef struct appdeps{


    //=====================std==============================================
    int (*printf)(const char *format, ...);
    int (*sprintf)(char *str, const char *format, ...);
    int (*snprintf)(char *str, appsize size, const char *format, ...);

    appsize (*strlen)(const char *s);
    char *(*strcpy)(char *dst, const char *src);
    
    //nuber conversions
    int (*atoi)(const char *str);
    double (*atof)(const char *str);

    //=====================request==============================================
    const apprequest *apprequest;
    const char * (*get_route)(const apprequest *apprequest);
    const char *(*get_method)(const apprequest *apprequest); 

    const char *(*get_headder)(const apprequest *apprequest, const char *key);
    const char *(*get_headder_key)(const apprequest *apprequest,int index);
    const char *(*get_headder_value)(const apprequest *apprequest,int index);

    const char *(*get_query_param)(const apprequest *apprequest, const char *key);
    const char *(*get_query_param_key)(const apprequest *apprequest,int index);
    const char *(*get_query_param_value)(const apprequest *apprequest,int index);
   
    const unsigned char *(*read_body)(const apprequest *apprequest, long size, long *readed_size);
    const appjson * (*read_json)(const apprequest *apprequest,long size);
    const appresponse *(*send_any)(const unsigned char *content,long content_size,const char *content_type, int status_code);
    const appresponse *(*send_text)(const char *text, int status_code);
    const appresponse *(*send_file)(const char *path,const char *content_type, int status_code);

} appdeps;





/* ===================== MAIN ===================== */

const appresponse * mainserver(appdeps *deps){
    return deps->send_any((unsigned char *)"Hello World", 11, "text/plain", 200);
}


