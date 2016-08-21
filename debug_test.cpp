#include "debug.hpp"
#include <unistd.h>

using namespace kdebug;

int main(){
    LOG(null) << "info logging\n";
    LOG(info) << "info logging\n";
    sleep(1);

    LOG(warning) << "warning logging\n";
    LOG(error) << "error logging\n";

    // debug.list();

    // debug << "Hello world!!!!\n";
    // debug << "Hello world!!!!\n";

    // debug.list();

    return 0;
}
