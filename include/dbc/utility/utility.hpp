#ifndef DBC_AUXI_HPP
#define DBC_AUXI_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/core/types.hpp"

DBC_BEGIN

Dstring join(Dstring splitor, const std::vector<Dstring> &elements, const std::initializer_list<Dstring> &filters={});

//============= Templates =============
template <typename Tp>
str toString(const Tp &v){
    throw Dexcept("Unsupported type.");
};

template<>
str toString<bool>(const bool &v){
    return v ? "true" : "false";
}

template<>
str toString<int>(const int &v){
    std::stringstream stream;
    stream << v;
    return stream.str();
}

template<>
str toString<long>(const long &v){
    std::stringstream stream;
    stream << v;
    return stream.str();
}

template<>
str toString<double>(const double &v){
    std::stringstream stream;
    stream << v;
    return stream.str();
}

template<>
str toString<barray>(const barray &array){
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
str toString<iarray>(const iarray &array){
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
str toString<larray>(const larray &array){
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
str toString<darray>(const darray &array){
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
str toString<sarray>(const sarray &array){
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


DBC_END
#endif