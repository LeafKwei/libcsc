#ifndef DBC_VALUE_HPP
#define DBC_VALUE_HPP

#include <vector>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/core/types.hpp"
#include "dbc/lex/PureLexer.hpp"
DBC_BEGIN

inline int baseOf(const Dstring &str){
    if(str.substr(0, 2) == "0x") return 16;
    return 10;
}


//============= Templates =============
class Dvalue{
public:
    Dvalue(const Dstring &value) : m_value(value){}

    template<typename Tp>
    Tp to();    

private:
    Dstring m_value;
};

template<typename Tp>
Tp Dvalue::to(){
    throw Dexcept("Unsupported type.");
}

template<>
bool Dvalue::to<bool>(){
    if(m_value == "true") return true;
    return false;
}

template<>
int Dvalue::to<int>(){
    return std::stoi(m_value, 0, baseOf(m_value));
}

template<>
long Dvalue::to<long>(){
    return std::stol(m_value, 0, baseOf(m_value));
}

template<>
double Dvalue::to<double>(){
    return std::stod(m_value);
}

template<>
str Dvalue::to<str>(){
    return m_value;
}

template<>
barray Dvalue::to<barray>(){
    barray array;
    CharMngr mngr(m_value);
    PureLexer lexer;

    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);

    }
}

template<>
iarray Dvalue::to<iarray>(){
   
}

template<>
larray Dvalue::to<larray>(){
    
}

template<>
darray Dvalue::to<darray>(){
 
}

template<>
sarray Dvalue::to<sarray>(){

}

DBC_END
#endif