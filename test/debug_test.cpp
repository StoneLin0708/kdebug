#include <unistd.h>
#include <iostream>
#include <string>
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

    //source name off
    DBG_SOURCE_NAME(false)
    DBG(INFO) << "dbg source name off";
    TIMER_SOURCE_NAME(false)
    TIMER(INFO) << "timer source name off";
    LOG_SOURCE_NAME(false)
    LOG(INFO) << "log source name off";

    //source name on
    DBG_SOURCE_NAME(true)
    DBG(INFO) << "dbg source name on";
    TIMER_SOURCE_NAME(true)
    TIMER(INFO) << "timer source name on";
    LOG_SOURCE_NAME(true)
    LOG(INFO) << "log source name on";

    //log to file
    SET_OUTPUT_FILE("kdebug")
    DBG(INFO) << "dbg to file";
    TIMER(INFO) << "timer to file";
    LOG(INFO) << "log to file";

    DBG_OUTPUT_FILE( false )
    TIMER_OUTPUT_FILE( false )
    LOG_OUTPUT_FILE( false )

    DBG(INFO) << "dbg file false";
    TIMER(INFO) << "timer file false";
    LOG(INFO) << "log file false";
    return 0;
}
