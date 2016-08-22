#include "kdebug.h"
#include "link_test.hpp"

int main(void)
{
    LOG(info) << "program starting...";
    link1();
    link2();

    return 0;
}
