#ifndef DBC_CORE_STRUCTS_HPP
#define DBC_CORE_STRUCTS_HPP

#include <memory>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

struct Dpair;
struct Ddomain;
using DpairPtr = std::shared_ptr<Dpair>;
using DdomainPtr = std::shared_ptr<Ddomain>;

struct Dpair{
    Dstring name;
    Dstring value;
    DpairPtr next;
    DpairPtr prev;
};

struct Ddomain{
    Dstring name;
    DpairPtr pairs;
    DdomainPtr parent;
    DdomainPtr child;
    DdomainPtr next;
    DdomainPtr prev;
};

DBC_END
#endif