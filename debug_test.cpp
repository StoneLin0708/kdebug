#include "debug.hpp"
#include <unistd.h>

using namespace kdebug;

int main(){
    LOG(null) << "info logging\n";
    LOG(info) << "info logging\n";
    sleep(1);

    debug.set_fileoutput("loggin.txt");

    LOG(file) << "file logging\n";

    LOG(warning) << "warning logging\n";
    LOG(error) << "error logging\n";

    return 0;
}
