#include "debug.hpp"
#include <iostream>

using namespace std;

namespace kdebug{

std::map<level,const char*> levelstring = {
    {info,"info"},
    {warning,"warning"},
    {error,"error"},
};

class dbg_construct{
public:
    dbg_construct(){ pdbg = new dbg();}
    ~dbg_construct(){ delete pdbg;}
    dbg* pdbg;
};

dbg_construct dbgc;
dbg &debug = *dbgc.pdbg;

dbg::dbg()
{
    starttime = Clock::now();
    flag_logged = true;
}

auto dbg::time(){
    return std::chrono::duration_cast
        <std::chrono::microseconds>
        (Clock::now()-starttime).count();
}

stringstream& dbg::operator<<(level l)
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

    return _ss;
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

void dbg::list(level l)
{
    if(!flag_logged)
        log();
    for(auto i=_log.begin();i!=_log.end();++i)
    {
        if( get<1>(*i) >= l)
            cout<< get<0>(*i)<< " "<< levelstring[get<1>(*i)]<< " : "<< get<2>(*i)<<'\n';
    }
};

}
