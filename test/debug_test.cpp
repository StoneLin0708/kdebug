#include <unistd.h>
#include <iostream>

#include "kdebug/kdebug.h"

int main(){
    LOG(null) << "info logging";
    LOG(info) << "info logging";
    sleep(1);

    SET_FILE("loggin.txt")

    LOG(warning) << "warning logging";
    LOG(error) << "error logging";

    LOG(file) << "file logging";
    LOG(file) << "file logging";

    DBG(null) << "nothing";
    DBG(info) << "info debugging";
    DBG(warning) << "warning debugging";
    DBG(error) << "error debugging";

    TIMER(null) << "nothing";
    TIMER(info) << "info timing";
    TIMER(warning) << "warning timing";
    TIMER(error) << "error timing";

    // std::cout << kdebug::debug.back();
    // std::cout << "test\n";
    return 0;
}
