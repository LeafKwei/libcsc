#ifndef DBC_CORE_STRUCTS_HPP
#define DBC_CORE_STRUCTS_HPP

#include <memory>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

struct Dpair;
struct Dscope;
using DpairPtr = std::shared_ptr<Dpair>;
using DscopePtr = std::shared_ptr<Dscope>;

struct Dpair{
    Dstring name;
    Dstring value;
    DpairPtr next;
};

struct Dscope{
    Dstring name;
    DpairPtr pairHead;
    DscopePtr parent;
    DscopePtr child;
    DscopePtr next;
};

DBC_END
#endif