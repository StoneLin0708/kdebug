#include "kdebug/kdebug.h"

int main(void) {
  LOG(KDEBUG_INFO, "info logging");
  LOG(KDEBUG_WARNING, "warning logging");
  LOG(KDEBUG_ERROR, "error logging");

  TIMER(KDEBUG_INFO, "info timing");
  TIMER(KDEBUG_WARNING, "warning timing");
  TIMER(KDEBUG_ERROR, "error timing");

  DATE(KDEBUG_INFO, "info date");
  DATE(KDEBUG_WARNING, "warning date");
  DATE(KDEBUG_ERROR, "error date");

  KDEBUG(KDEBUG_INFO, "info debugging");
  KDEBUG(KDEBUG_WARNING, "warning debugging");
  KDEBUG(KDEBUG_ERROR, "error debugging");
  return 0;
}
