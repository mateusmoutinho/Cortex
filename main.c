

#include "dependencies/doTheWorldOne.c"
#include "dependencies/CWebStudioOne.c"




CwebHttpResponse *main_server(CwebHttpRequest *request) {
    return cweb_send_text("Hello World", 200);
}

int main(int argc, char *argv[]) {
    CwebServer server = newCwebSever(5000, main_server);
    CwebServer_start(&server);
    return 0;
}

#ifdef DEFINE_DEPENDENCIES
#include "dependencies/CArgvParse.c"

#include "dependencies/CTextEngine.c"
#include "dependencies/CWebStudio.c"
#include "dependencies/doTheWorldOne.c"

#endif 