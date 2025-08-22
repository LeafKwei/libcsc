#ifndef CSC_VALUE_HPP
#define CSC_VALUE_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

struct CscValue{
    explicit CscValue(const CscStr &val, ValueType tp) : value(val), type(tp){}
    operator CscStr() {return value;}
    operator const char*() {return value.c_str();}

    CscStr value;
    ValueType type;
};

CSC_END
#endif