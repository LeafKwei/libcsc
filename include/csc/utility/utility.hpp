#ifndef CSC_UTILITY_HPP
#define CSC_UTILITY_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/lex/types.hpp"
#include "csc/syntax/types.hpp"
#include "csc/core/types.hpp"

CSC_BEGIN

CscStr join(CscStr splitor, const std::vector<CscStr> &elements, const std::initializer_list<CscStr> &filters={});
int baseOf(const CscStr &str);
CscStr toEscapingString(const CscStr &str);

//============= Templates =============
template <typename Tp>
inline CscStr toString(const Tp &v){
    throw CscExcept("Unsupported type.");
};

template<>
inline CscStr toString<bool>(const bool &v){
    return v ? "true" : "false";
}

template<>
inline CscStr toString<int>(const int &v){
    std::stringstream stream;
    stream << v;
    return stream.str();
}

template<>
inline CscStr toString<long>(const long &v){
    std::stringstream stream;
    stream << v;
    return stream.str();
}

template<>
inline CscStr toString<double>(const double &v){
    std::stringstream stream;
    stream << v;
    return stream.str();
}


CSC_END
#endif