#include "kdebug.h"
#include <unistd.h>
#include <iostream>

using namespace kdebug;

int main(){
    LOG(null) << "info logging";
    LOG(info) << "info logging";
    sleep(1);

    log.set_fileoutput("loggin.txt");

    LOG(warning) << "warning logging";
    LOG(error) << "error logging";

    LOG(file) << "file logging";
    LOG(file) << "file logging";

    // std::cout << kdebug::debug.back();
    // std::cout << "test\n";
    return 0;
}
