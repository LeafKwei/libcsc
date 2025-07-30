#ifndef DBC_CORE_TYPES_HPP
#define DBC_CORE_TYPES_HPP

#include <memory>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

struct Dpair;
struct Ddomain;
using DpairPtr = std::shared_ptr<Dpair>;
using DdomainPtr = std::shared_ptr<Ddomain>;
using DpairWkr = std::weak_ptr<Dpair>;
using DdomainWkr = std::weak_ptr<Ddomain>;

struct Dpair{
    Dstring name;
    Dstring value;
    DpairPtr next;
    DpairWkr prev;
};

struct Ddomain{
    Dstring name;
    DpairPtr pairs;
    DdomainPtr child;
    DdomainPtr next;
    DdomainWkr parent;
    DdomainWkr prev;
};

DBC_END
#endif