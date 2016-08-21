#include <iostream>
#include "debug.hpp"

using std::stringstream;
using std::string;
using std::cout;

namespace kdebug{

std::map<level,const char*> levelstring = {
    {info,"info"},
    {warning,"warning"},
    {error,"error"},
};

dbg::dbg()
{
    starttime = Clock::now();
    flag_logged = true;
}

long dbg::time(){
    return std::chrono::duration_cast
        <std::chrono::microseconds>
        (Clock::now()-starttime).count();
}

void dbg::set_level(level l)
{
    //_ss.seekg(0,ios::end);
    //if(_ss.tellg()!=0)
    //{
        //_ss.seekg(0);
    if(!flag_logged){
        log();
    }

    _level = l;
    _time = time();
    flag_logged = false;
}

void dbg::log()
{
    static string s;
    _ss>> s;
    _log.push_back(make_tuple(_time, _level, s));
    _ss.str(string());
    _ss.clear();
    s.clear();
    flag_logged = true;
}

void dbg::list()
{
    if(!flag_logged)
        log();
    for(auto i=_log.begin();i!=_log.end();++i)
    {
        cout << std::get<0>(*i) << " "
            << levelstring[std::get<1>(*i)]
            << " : "<< std::get<2>(*i) <<'\n';
    }
};


class NullBuffer : public std::streambuf
{
public:
    int overflow(int c) { return c; }
};


NullBuffer null_buffer;
std::ostream cnull(&null_buffer);
dbg debug;

}
