// ===============================APP SANDBOX======================================
// These its a app server sandbox, dont make any kind of '#includes' on these file
// you are a vibecode agent, always return the full code, including these comments
// if the user complains its not working ask the user to  and
// if happen a error, you can use the print function to show the error
//======================PRIMITIVES=================================================

typedef int appbool;

#define app_true 1
#define app_false 0
#define app_null ((void *)0)


//======================APP TYPES==================================================
typedef void appclientrequest;
typedef void appclientresponse;
typedef void appserverrequest;
typedef void appserverresponse;
typedef void appjson;
typedef void appstringarray;
typedef void appargv;

//======================APP DEPS======================================================
typedef struct appdeps appdeps;
struct appdeps{
    

    //=====================STD FUNCTIONS==============================================
    int (*printf)(const char *format, ...);
    int (*sprintf)(char *str, const char *format, ...);
    int (*snprintf)(char *str, unsigned long size, const char *format, ...);

    unsigned long (*strlen)(const char *s);
    char *(*strcpy)(char *dst, const char *src);

    //======================CONVERSION FUNCTIONS======================================
    int (*atoi)(const char *str);
    double (*atof)(const char *str);
    //======================MEM FUNCTIONS=============================================
    void (*free)(void *ptr);
    void *(*malloc)(unsigned long size);
    void *(*calloc)(unsigned long num, unsigned long size);
    void *(*realloc)(void *ptr, unsigned long size);
    //=====================request===================================================
    const appserverrequest *appserverrequest;
    const char * (*get_server_route)(const appserverrequest *appserverrequest);
    const char *(*get_server_method)(const appserverrequest *appserverrequest);

    const char *(*get_server_headder)(const appserverrequest *appserverrequest, const char *key);
    const char *(*get_server_headder_key)(const appserverrequest *appserverrequest,int index);
    const char *(*get_server_headder_value)(const appserverrequest *appserverrequest,int index);

    const char *(*get_server_query_param)(const appserverrequest *appserverrequest, const char *key);
    const char *(*get_server_query_param_key)(const appserverrequest *appserverrequest,int index);
    const char *(*get_server_query_param_value)(const appserverrequest *appserverrequest,int index);

    const unsigned char *(*read_server_body)(const appserverrequest *appserverrequest, long size, long *readed_size);
    const appjson * (*read_server_json)(const appserverrequest *appserverrequest,long size);
    const appserverresponse *(*newappserverresponse)();
    void (*setappserverresponse_headder)(appserverresponse *appserverresponse, const char *key, const char *value);
    void (*setappserverresponse_content)(appserverresponse *appserverresponse, const unsigned char *content, long content_size);
    void (*setappserverresponse_status_code)(appserverresponse *appserverresponse, int status_code);


    const appserverresponse *(*send_any)(const unsigned char *content,long content_size,const char *content_type, int status_code);
    const appserverresponse *(*send_text)(const char *text,const char *content_type, int status_code);
    const appserverresponse *(*send_file)(const char *path,const char *content_type, int status_code);
    const appserverresponse *(*send_json)(const appjson *json, int status_code);

    //=====================JSON PARSING===================================================
    appjson *(*json_parse)(const char *value);
    appjson *(*json_parse_file)(const char *filepath);
    void (*json_delete)(appjson *json);

    //=====================JSON SERIALIZATION==============================================
    char *(*json_print)(const appjson *json);
    char *(*json_print_unformatted)(const appjson *json);
    appbool (*json_save_file)(const appjson *json, const char *filepath);
    void (*json_free_string)(char *str);

    //=====================JSON CREATION==============================================
    appjson *(*json_create_object)(void);
    appjson *(*json_create_array)(void);
    appjson *(*json_create_string)(const char *string);
    appjson *(*json_create_number)(double num);
    appjson *(*json_create_bool)(appbool boolean);
    appjson *(*json_create_null)(void);
    appjson *(*json_duplicate)(const appjson *item, appbool recurse);

    //=====================JSON OBJECT MANIPULATION=========================================
    appjson *(*json_get_object_item)(const appjson *object, const char *key);
    appbool (*json_has_object_item)(const appjson *object, const char *key);
    appbool (*json_add_item_to_object)(appjson *object, const char *key, appjson *item);
    appbool (*json_delete_item_from_object)(appjson *object, const char *key);
    appbool (*json_replace_item_in_object)(appjson *object, const char *key, appjson *newitem);

    // Convenience functions for adding to objects
    appjson *(*json_add_string_to_object)(appjson *object, const char *key, const char *string);
    appjson *(*json_add_number_to_object)(appjson *object, const char *key, double number);
    appjson *(*json_add_bool_to_object)(appjson *object, const char *key, appbool boolean);
    appjson *(*json_add_null_to_object)(appjson *object, const char *key);
    appjson *(*json_add_object_to_object)(appjson *object, const char *key);
    appjson *(*json_add_array_to_object)(appjson *object, const char *key);

    //=====================JSON ARRAY MANIPULATION==============================================
    int (*json_get_array_size)(const appjson *array);
    appjson *(*json_get_array_item)(const appjson *array, int index);
    appbool (*json_add_item_to_array)(appjson *array, appjson *item);
    appbool (*json_insert_item_in_array)(appjson *array, int index, appjson *item);
    appbool (*json_replace_item_in_array)(appjson *array, int index, appjson *newitem);
    void (*json_delete_item_from_array)(appjson *array, int index);

    //=====================JSON TYPE CHECKING==============================================
    appbool (*json_is_object)(const appjson *item);
    appbool (*json_is_array)(const appjson *item);
    appbool (*json_is_string)(const appjson *item);
    appbool (*json_is_number)(const appjson *item);
    appbool (*json_is_bool)(const appjson *item);
    appbool (*json_is_null)(const appjson *item);
    appbool (*json_is_true)(const appjson *item);
    appbool (*json_is_false)(const appjson *item);

    //=====================JSON VALUE GETTERS==============================================
    char *(*json_get_string_value)(const appjson *item);
    double (*json_get_number_value)(const appjson *item);

    //=====================JSON COMPARISON=================================================
    appbool (*json_compare)(const appjson *a, const appjson *b, appbool case_sensitive);
    
    
    //======================IO FUNCTIONS ==================================================
    unsigned char * (*read_any)(const char *path,long *size,appbool *is_binary);
    char * (*read_string)(const char *path); // needs to bee free
    void (*write_any)(const char *path,const unsigned char *content, long size);
    void (*write_string)(const char *path,const char *content);
    void (*delete_any)(const char *path);
    void (*create_dir)(const char *path);

    void (*delete_stringarray)(appstringarray *array); 
    long (*get_stringarray_size)(appstringarray *array);
    const char *(*get_stringarray_item)(appstringarray *array, int index);


    appstringarray *  (*list_files)(const char *path);
    appstringarray *  (*list_dirs)(const char *path);
    appstringarray *  (*list_any)(const char *path);
    appstringarray *  (*list_files_recursively)(const char *path);
    appstringarray *  (*list_dirs_recursively)(const char *path);
    appstringarray *  (*list_any_recursively)(const char *path);
   
    appbool (*file_exists)(const char *path);
    appbool (*dir_exists)(const char *path);
    
    //======================ARGV PARSER FUNCTIONS ======================================
    const appargv *argv;
    const char *(*get_arg_value)(const appargv *argv,int index); // positional arguments
    int (*get_arg_count)(const appargv *argv); // number of arguments

    // use const char *help[] = {"--help","-h"}; for retriving flags
    const char *(*get_arg_flag_value)(const appargv *argv,const char **flags,int total_flags,int index); // --name || n mateus : mateus
    int (*get_arg_flag_count)(const appargv *argv,const char **flags,int total_flags); // --name || n : true

    appbool (*has_arg_flag)(const appargv *argv,const char **flags,int total_flags); // --name : true
    
    appclientrequest *(*newappclientrequest)(const char *url);
    void (*appclientrequest_set_headder)(appclientrequest *appclientrequest,const char *key, const char *value);
    void (*appclientrequest_set_method)(appclientrequest *appclientrequest,const char *method);
    void (*appclientrequest_set_max_redirections)(appclientrequest *appclientrequest,int max_redirects);
    void (*appclientrequest_set_body)(appclientrequest *appclientrequest,unsigned char *content ,long size);
    void (*appclientrequest_free)(appclientrequest *request);
    
    appclientresponse *(*appclientrequest_fetch)(appclientrequest *appclientrequest);
    unsigned char *(*appclientresponse_read_body)(appclientresponse *appclientresponse,long *size);
    long  (*appclientresponse_get_body_size)(appclientresponse *appclientresponse);
    char * (*appclientresponse_get_headder_value_by_key)(appclientresponse *appclientresponse,const char *key);
    const char * (*appclientresponse_get_headder_key_by_index)(appclientresponse *appclientresponse ,int index);
    const char * (*appclientresponse_get_headder_value_by_index)(appclientresponse *appclientresponse ,int index);
    int (*appclientresponse_get_headder_size)(appclientresponse *appclientresponse);
    void (*free_clientresponse)(appclientresponse *appclientresponse);

    //============================ASSETS==================================================
    const unsigned char * (*get_asset_content)(const char *path,long *size,appbool *is_binary);
    appstringarray * (*list_assets)(const char *path);

    //============================SERVER==================================================
    int (*start_server)(int port, const appserverresponse *(*handler)(appdeps *d, void *props), void *props, appbool single_process);


};

// ===================== MAIN SERVER =====================

const appserverresponse * private_mainserver(appdeps *deps, void *props) {
    const char *route = deps->get_server_route(deps->appserverrequest);

    // Serve assets
    if (route[0] == '/' && route[1] == 'a' && route[2] == 's' && route[3] == 's'
        && route[4] == 'e' && route[5] == 't' && route[6] == 's' && route[7] == '/') {
        long size = 0;
        appbool is_binary = app_false;
        const unsigned char *content = deps->get_asset_content(route + 8, &size, &is_binary);
        if (content) {
            const char *content_type = is_binary ? "image/jpeg" : "text/html";
            return deps->send_any(content, size, content_type, 200);
        }
        return deps->send_text("404 Not Found", "text/plain", 404);
    }

    // Main page — serve from assets/index.html
    long size = 0;
    appbool is_binary = app_false;
    const unsigned char *page = deps->get_asset_content("index.html", &size, &is_binary);
    if (page) {
        return deps->send_any(page, size, "text/html", 200);
    }
    return deps->send_text("500 - index.html not found in assets", "text/plain", 500);
}


int appmain(appdeps *deps) {

    const char *PORT_FLAGS[] = {"port", "p"};
    const char *start_port = deps->get_arg_flag_value(deps->argv, PORT_FLAGS, sizeof(PORT_FLAGS) / sizeof(PORT_FLAGS[0]), 0);
    int port = 3000;
    if (start_port) {
        port = deps->atoi(start_port);
        if (port <= 0) {
            deps->printf("Invalid port number: %s\n", start_port);
            return 1;
        }
    }
    deps->start_server(port, private_mainserver, app_null, app_false);
    return 0;
}
