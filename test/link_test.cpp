#include "link_test.hpp"
#include "kdebug/kdebug.h"

int main(void) {
  LOG(info) << "program starting...";
  link1();
  link2();
  return 0;
}
