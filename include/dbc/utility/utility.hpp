#ifndef DBC_UTILITY_HPP
#define DBC_UTILITY_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/core/types.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/syntax/types.hpp"

DBC_BEGIN

Dstring join(Dstring splitor, const std::vector<Dstring> &elements, const std::initializer_list<Dstring> &filters={});
int baseOf(const Dstring &str);

//============= Templates =============
template <typename Tp>
inline str toString(const Tp &v){
    throw Dexcept("Unsupported type.");
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

DBC_END
#endif