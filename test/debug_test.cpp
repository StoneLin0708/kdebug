#include <unistd.h>
#include <iostream>

#include "kdebug/kdebug.h"

int main(){
    // log test
    LOG(INFO) << "info logging";
    sleep(1);
    LOG(INFO) << "info logging";
    sleep(1);
    LOG(INFO) << "info logging";
    LOG(WARNING) << "warning logging";
    LOG(ERROR) << "error logging";
    LOG(null) << "info logging";

    // debug test
    DBG(INFO) << "info debugging";
    sleep(1);
    DBG(INFO) << "info debugging";
    sleep(1);
    DBG(INFO) << "info debugging";
    DBG(WARNING) << "warning debugging";
    DBG(ERROR) << "error debugging";
    DBG(null) << "nothing";

    // timer test
    TIMER(INFO) << "info timing";
    sleep(1);
    TIMER(INFO) << "info timing";
    sleep(1);
    TIMER(INFO) << "info timing";
    TIMER(WARNING) << "warning timing";
    TIMER(ERROR) << "error timing";
    TIMER(null) << "nothing";
    return 0;
}
