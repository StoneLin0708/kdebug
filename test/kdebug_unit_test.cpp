#include "kdebug/kdebug.h"
#include <unistd.h>
#include <iostream>
#include <string>

using namespace kdebug;

class Object {
 public:
  Object() { LOG(info) << "static initialization..."; }
} obj;

int main(int, char* argv[]) {
  // log test
  LOG(info) << "info logging";
  LOG(INFO) << "info logging";
  sleep(1);
  LOG(INFO) << "after waiting a second...";
  sleep(1);
  LOG(INFO) << "after waiting a second...";
  sleep(1);
  LOG(WARNING) << "warning logging after a second";
  sleep(1);
  LOG(ERROR) << "error logging after a second";

  // timer test
  TIMER(INFO) << "info timing";
  sleep(1);
  TIMER(INFO) << "info timing";
  sleep(1);
  TIMER(INFO) << "info timing";
  TIMER(WARNING) << "warning timing";
  TIMER(ERROR) << "error timing";

  // date test
  DATE(INFO) << "info date";
  sleep(1);
  DATE(INFO) << "info date";
  sleep(1);
  DATE(INFO) << "info date";
  DATE(WARNING) << "warning date";
  DATE(ERROR) << "error date";

  // debug test
  KDEBUG(INFO) << "info debugging";
  sleep(1);
  KDEBUG(INFO) << "info debugging";
  sleep(1);
  KDEBUG(INFO) << "info debugging";
  KDEBUG(WARNING) << "warning debugging";
  KDEBUG(ERROR) << "error debugging";

  // output to file test
  kdebug::OutputToFile(argv[0]);
  LOG(info) << "info logging to file";
  LOG(INFO) << "info logging to file";
  sleep(1);
  LOG(INFO) << "after waiting a second...";
  sleep(1);
  LOG(INFO) << "after waiting a second...";
  sleep(1);
  LOG(WARNING) << "warning logging after a second";
  sleep(1);
  LOG(ERROR) << "error logging after a second";
  kdebug::CloseOutputFile();

  LOG(info) << "program end.";
  return 0;
}
