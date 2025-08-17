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
inline bool Dvalue::to<bool>(){        //'inline' is used to avoid ODR(One Definition Rule)
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
        if(token.type == TokenType::Unexcepted){
            mngr.forward();
            continue;
        }

        auto v = (token.buffer == "true") ? true : false;
        array.push_back(v);
    }

    return array;
}

template<>
inline iarray Dvalue::to<iarray>(){
    iarray array;
    CharMngr mngr(m_value);
    PureLexer lexer;

    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);
        if(token.type == TokenType::Unexcepted){
            mngr.forward();
            continue;
        }

        auto v = std::stoi(token.buffer, 0, baseOf(token.buffer));
        array.push_back(v);
    }

    return array;
}

template<>
inline larray Dvalue::to<larray>(){
    larray array;
    CharMngr mngr(m_value);
    PureLexer lexer;

    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);
        if(token.type == TokenType::Unexcepted){
            mngr.forward();
            continue;
        }

        auto v = std::stol(token.buffer, 0, baseOf(token.buffer));
        array.push_back(v);
    }

    return array;
}

template<>
inline darray Dvalue::to<darray>(){
    darray array;
    CharMngr mngr(m_value);
    PureLexer lexer;

    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);
        if(token.type == TokenType::Unexcepted){
            mngr.forward();
            continue;
        }

        auto v = std::stod(token.buffer, 0);
        array.push_back(v);
    }

    return array;
}

template<>
inline sarray Dvalue::to<sarray>(){
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