#ifndef DBC_ITERATOR_HPP
#define DBC_ITERATOR_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/core/types.hpp"
DBC_BEGIN

class Diterator{
public:
    virtual void enter(const Dstring &name) =0;
    virtual void exit(const Dstring &name) =0;
    virtual void pair(const Dstring &name, const Dstring &value, ValueType type) =0;
};

DBC_END
#endif