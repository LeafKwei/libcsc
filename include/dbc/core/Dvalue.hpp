#ifndef DBC_VALUE_HPP
#define DBC_VALUE_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/context/types.hpp"
DBC_BEGIN

struct Dvalue{
    explicit Dvalue(const Dstring &val, ValueType tp) : value(val), type(tp){}
    operator Dstring() {return value;}
    operator const char*() {return value.c_str();}

    Dstring value;
    ValueType type;
};

DBC_END
#endif