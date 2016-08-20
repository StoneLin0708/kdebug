#include "debug.hpp"

using namespace kdebug;

int main(){
    debug<<info<<"hi1"<<"??";
    debug<<warning<<"hi2";
    debug<<error<<"hi3";
    debug.list();
    debug.list(warning);
    debug.list(info);

}
