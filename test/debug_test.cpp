#include "debug.hpp"
#include <unistd.h>

using namespace kdebug;

int main(){
    LOG(null) << "info logging";
    LOG(info) << "info logging";
    sleep(1);

    debug.set_fileoutput("loggin.txt");

    LOG(file) << "file logging";
    LOG(warning) << "warning logging";
    LOG(error) << "error logging";
    return 0;
}
