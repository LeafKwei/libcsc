#ifndef DBC_ITEM_HPP
#define DBC_ITEM_HPP

#include <vector>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/context/types.hpp"
#include "dbc/lex/PureLexer.hpp"
#include "dbc/utility/utility.hpp"
DBC_BEGIN

//============= Templates =============
class Ditem{
public:
    explicit Ditem(const Dstring &value, ValueType type) : m_value(value), m_type(type){}

    template<typename Tp>
    Tp to();    

private:
    Dstring m_value;
    ValueType m_type;
};

template<typename Tp>
Tp Ditem::to(){
    throw Dexcept("Unsupported type.");
}

template<>
inline bool Ditem::to<bool>(){        //'inline' is used to avoid ODR(One Definition Rule)
    if(m_type != ValueType::Bool) throw Dexcept("Incompatible type.");
    if(m_value == "true") return true;
    return false;
}

template<>
inline int Ditem::to<int>(){
    if(m_type != ValueType::Integer) throw Dexcept("Incompatible type.");
    return std::stoi(m_value, 0, baseOf(m_value));
}

template<>
inline long Ditem::to<long>(){
    if(m_type != ValueType::Integer) throw Dexcept("Incompatible type.");
    return std::stol(m_value, 0, baseOf(m_value));
}

template<>
inline double Ditem::to<double>(){
    if(m_type != ValueType::Double) throw Dexcept("Incompatible type.");
    return std::stod(m_value);
}

template<>
inline str Ditem::to<str>(){
    return m_value;
}

template<>
inline barray Ditem::to<barray>(){
    if(m_type != ValueType::Bools) throw Dexcept("Incompatible type.");

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
inline iarray Ditem::to<iarray>(){
    if(m_type != ValueType::Integers) throw Dexcept("Incompatible type.");

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
inline larray Ditem::to<larray>(){
    if(m_type != ValueType::Integers) throw Dexcept("Incompatible type.");

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
inline darray Ditem::to<darray>(){
    if(m_type != ValueType::Doubles) throw Dexcept("Incompatible type.");

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
inline sarray Ditem::to<sarray>(){
    if(m_type != ValueType::Strings) throw Dexcept("Incompatible type.");

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