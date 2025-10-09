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

String join(String splitor, const std::vector<String> &elements, const std::initializer_list<String> &filters={});
String valueToString(const Value &val, ValueType tp);
String toEscapingString(crString str);

//=================== toString系列函数 ===================
inline String toString(CppType<ValueType::Bool>::type raw){
    return (raw) ? "true" : "false";
}

inline String toString(CppType<ValueType::Integer>::type raw){
    std::stringstream sstream;
    sstream << raw;
    return sstream.str();
}

inline String toString(CppType<ValueType::Double>::type raw){
    std::stringstream sstream;
    sstream << raw;
    return sstream.str();
}

inline String toString(CppType<ValueType::String>::type raw){
    return raw;
}

CSC_END
#endif