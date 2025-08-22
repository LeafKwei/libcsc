#ifndef CSC_UTILITY_HPP
#define CSC_UTILITY_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/core/types.hpp"
#include "csc/lex/types.hpp"
#include "csc/syntax/types.hpp"

CSC_BEGIN

CscStr join(CscStr splitor, const std::vector<CscStr> &elements, const std::initializer_list<CscStr> &filters={});
int baseOf(const CscStr &str);

//============= Templates =============
template <typename Tp>
inline str toString(const Tp &v){
    throw CscExcept("Unsupported type.");
};

template<>
inline str toString<bool>(const bool &v){
    return v ? "true" : "false";
}

template<>
inline str toString<int>(const int &v){
    std::stringstream stream;
    stream << v;
    return stream.str();
}

template<>
inline str toString<long>(const long &v){
    std::stringstream stream;
    stream << v;
    return stream.str();
}

template<>
inline str toString<double>(const double &v){
    std::stringstream stream;
    stream << v;
    return stream.str();
}

template<>
inline str toString<barray>(const barray &array){
    std::stringstream stream;
    int idx = 0;

    for(; idx < array.size(); idx++){
        stream << toString(array.at(idx));
        if(idx + 1 < array.size()){
            stream << ",";
        }
    }

    return stream.str();
}

template<>
inline str toString<iarray>(const iarray &array){
    std::stringstream stream;
    int idx = 0;

    for(; idx < array.size(); idx++){
        stream << array.at(idx);
        if(idx + 1 < array.size()){
            stream << ",";
        }
    }

    return stream.str();
}

template<>
inline str toString<larray>(const larray &array){
    std::stringstream stream;
    int idx = 0;

    for(; idx < array.size(); idx++){
        stream << array.at(idx);
        if(idx + 1 < array.size()){
            stream << ",";
        }
    }

    return stream.str();
}

template<>
inline str toString<darray>(const darray &array){
    std::stringstream stream;
    int idx = 0;

    for(; idx < array.size(); idx++){
        stream << array.at(idx);
        if(idx + 1 < array.size()){
            stream << ",";
        }
    }

    return stream.str();
}

template<>
inline str toString<sarray>(const sarray &array){
    std::stringstream stream;
    int idx = 0;

    for(; idx < array.size(); idx++){
        stream << "\"" << array.at(idx) << "\"";
        if(idx + 1 < array.size()){
            stream << ",";
        }
    }

    return stream.str();
}

CSC_END
#endif