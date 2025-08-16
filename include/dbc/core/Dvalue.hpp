#ifndef DBC_VALUE_HPP
#define DBC_VALUE_HPP

#include <vector>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/core/types.hpp"
#include "dbc/lex/PureLexer.hpp"
DBC_BEGIN

using str = Dstring;
using barray = std::vector<bool>;
using iarray = std::vector<int>;
using larray = std::vector<long>;
using darray = std::vector<double>;
using sarray = std::vector<str>;

class Dvalue{
public:
    Dvalue(ValueType type, const Dstring &value) : m_type(type), m_value(value){}

    template<typename Tp>
    Tp to();    

private:
    ValueType m_type;
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
    return std::stoi(m_value);
}

template<>
long Dvalue::to<long>(){
    return std::stol(m_value);
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
        if(token.type == TokenType::Unexcepted){
            mngr.forward();
            continue;
        }

        if(token.buffer == "true"){
            array.push_back(true);
            continue;
        }

        array.push_back(false);
    }

    return array;
}

template<>
iarray Dvalue::to<iarray>(){
    iarray array;
    CharMngr mngr(m_value);
    PureLexer lexer;

    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);
        if(token.type == TokenType::Unexcepted){
            mngr.forward();
            continue;
        }

        array.push_back(std::stoi(token.buffer));
    }

    return array;
}

template<>
larray Dvalue::to<larray>(){
    larray array;
    CharMngr mngr(m_value);
    PureLexer lexer;

    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);
        if(token.type == TokenType::Unexcepted){
            mngr.forward();
            continue;
        }

        array.push_back(std::stol(token.buffer));
    }

    return array;  
}

template<>
darray Dvalue::to<darray>(){
    darray array;
    CharMngr mngr(m_value);
    PureLexer lexer;

    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);
        if(token.type == TokenType::Unexcepted){
            mngr.forward();
            continue;
        }

        array.push_back(std::stod(token.buffer));
    }

    return array;  
}

template<>
sarray Dvalue::to<sarray>(){
    sarray array;
    CharMngr mngr(m_value);
    PureLexer lexer;

    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);
        if(token.type == TokenType::Unexcepted){
            mngr.forward();
            continue;
        }

        array.push_back(token.buffer);
    }

    return array;  
}

DBC_END
#endif