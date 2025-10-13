#ifndef CSC_UTILITY_HPP
#define CSC_UTILITY_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/lex/types.hpp"
#include "csc/context/types.hpp"
#include "csc/syntax/types.hpp"
#include "csc/core/types.hpp"
CSC_BEGIN

String valueToString(crValue value, ValueType tp);
String toEscapingString(crString str);

//=================== 内联函数 //===================
inline bool isBoolString(crString str){
    return (str == "true") || (str == "false");
}

//=================== toString系列函数 ===================
/* 由于重载会导致某些类型(如int)因为隐式类型转换而出现模糊匹配错误，因此需要使用模板结合特例化实现toString函数 */
template<typename T>
inline String toString(T raw){
    return "";
}

template<>
inline String toString<CppType<ValueType::Bool>::type>(CppType<ValueType::Bool>::type raw){
    return (raw) ? "true" : "false";
}

template<>
inline String toString<CppType<ValueType::Integer>::type>(CppType<ValueType::Integer>::type raw){
    std::stringstream sstream;
    sstream << raw;
    return sstream.str();
}

template<>
inline String toString<CppType<ValueType::Double>::type>(CppType<ValueType::Double>::type raw){
    std::stringstream sstream;
    sstream << raw;
    return sstream.str();
}

template<>
inline String toString<CppType<ValueType::String>::type>(CppType<ValueType::String>::type raw){
    return raw;
}

CSC_END
#endif