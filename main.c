#include "wrapper/imports/imports.dep_define.h"



int main(int argc, char *argv[]) {
    global_argv = newCArgvParse(argc, argv);
    global_appdeps.argv = &global_argv;
    return appmain(&global_appdeps);
}
