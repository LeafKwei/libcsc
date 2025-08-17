#ifndef DBC_VALUE_HPP
#define DBC_VALUE_HPP

#include <vector>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/core/types.hpp"
#include "dbc/lex/PureLexer.hpp"
#include "dbc/utility/utility.hpp"
DBC_BEGIN

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
inline bool Dvalue::to<bool>(){
    if(m_value == "true") return true;
    return false;
}

template<>
inline int Dvalue::to<int>(){
    return std::stoi(m_value, 0, baseOf(m_value));
}

template<>
inline long Dvalue::to<long>(){
    return std::stol(m_value, 0, baseOf(m_value));
}

template<>
inline double Dvalue::to<double>(){
    return std::stod(m_value);
}

template<>
inline str Dvalue::to<str>(){
    return m_value;
}

template<>
inline barray Dvalue::to<barray>(){
    barray array;
    CharMngr mngr(m_value);
    PureLexer lexer;

    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);
        
    }
}

template<>
inline iarray Dvalue::to<iarray>(){
   
}

template<>
inline larray Dvalue::to<larray>(){
    
}

template<>
inline darray Dvalue::to<darray>(){
 
}

template<>
inline sarray Dvalue::to<sarray>(){

}

DBC_END
#endif