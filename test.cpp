#include "debug.hpp"
#include <iostream>

using namespace kdebug;
using namespace std;

int main(){
    debug<<info<<"hi1"<<"??";
    debug<<warning<<"hi2";
    debug<<error<<"hi3"<<" a b c";
    debug.list(info);
    cout<< *debug.begin()<< '\n';
    cout<< debug.back()<< '\n';

}
