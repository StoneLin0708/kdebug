#include <unistd.h>
#include <iostream>

#include "kdebug/kdebug.h"

int main(){
    // log test
    sleep(2);
    LOG(info) << "info logging";
    LOG(warning) << "warning logging";
    LOG(error) << "error logging";
    LOG(null) << "info logging";

    // debug test
    sleep(1);
    DBG(info) << "info debugging";
    DBG(warning) << "warning debugging";
    DBG(error) << "error debugging";
    DBG(null) << "nothing";

    // timer test
    sleep(1);
    TIMER(info) << "info timing";
    TIMER(warning) << "warning timing";
    TIMER(error) << "error timing";
    TIMER(null) << "nothing";
    return 0;
}
