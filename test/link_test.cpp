#include "kdebug.h"
#include "link_test.hpp"

int main(void)
{
    LOG(kdebug::info) << "program starting...\n";
    link1();
    link2();

    return 0;
}
