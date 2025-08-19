#ifndef DBC_CORE_TYPES_HPP
#define DBC_CORE_TYPES_HPP

#include <vector>
#include <memory>
#include <map>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

struct Dpair;
struct Ddomain;
using DpairPtr = std::shared_ptr<Dpair>;
using DdomainPtr = std::shared_ptr<Ddomain>;
using DpairWkr = std::weak_ptr<Dpair>;
using DdomainWkr = std::weak_ptr<Ddomain>;

using str = Dstring;
using barray = std::vector<bool>;
using iarray = std::vector<int>;
using larray = std::vector<long>;
using darray = std::vector<double>;
using sarray = std::vector<str>;

enum class ValueType{
    Unknown, 
    Bool, Integer, Double, String,
    Bools, Integers, Doubles, Strings
};

struct Dpair{
    ValueType type;
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