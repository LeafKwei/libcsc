#ifndef CSC_ITEM_HPP
#define CSC_ITEM_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/context/types.hpp"
#include "csc/lex/PureLexer.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

//============= Templates =============
class CscItem{
public:
    explicit CscItem(const CscStr &value, ValueType type) : m_value(value), m_type(type){}

    template<typename Tp>
    Tp to();    

private:
    CscStr m_value;
    ValueType m_type;
};

template<typename Tp>
Tp CscItem::to(){
    throw CscExcept("Unsupported type.");
}

template<>
inline bool CscItem::to<bool>(){        //'inline' is used to avoid ODR(One Definition Rule)
    if(m_type != ValueType::Bool) throw CscExcept("Incompatible type.");
    if(m_value == "true") return true;
    return false;
}

template<>
inline int CscItem::to<int>(){
    if(m_type != ValueType::Integer) throw CscExcept("Incompatible type.");
    return std::stoi(m_value, 0, baseOf(m_value));
}

template<>
inline long CscItem::to<long>(){
    if(m_type != ValueType::Integer) throw CscExcept("Incompatible type.");
    return std::stol(m_value, 0, baseOf(m_value));
}

template<>
inline double CscItem::to<double>(){
    if(m_type != ValueType::Double) throw CscExcept("Incompatible type.");
    return std::stod(m_value);
}

template<>
inline str CscItem::to<str>(){
    return m_value;
}

template<>
inline barray CscItem::to<barray>(){
    if(m_type != ValueType::Bools) throw CscExcept("Incompatible type.");

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
inline iarray CscItem::to<iarray>(){
    if(m_type != ValueType::Integers) throw CscExcept("Incompatible type.");

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
inline larray CscItem::to<larray>(){
    if(m_type != ValueType::Integers) throw CscExcept("Incompatible type.");

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
inline darray CscItem::to<darray>(){
    if(m_type != ValueType::Doubles) throw CscExcept("Incompatible type.");

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
inline sarray CscItem::to<sarray>(){
    if(m_type != ValueType::Strings) throw CscExcept("Incompatible type.");

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

CSC_END
#endif