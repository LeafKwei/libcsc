#ifndef CSC_CORE_TYPES_HPP
#define CSC_CORE_TYPES_HPP

#if 0
#include <vector>
#include <memory>
#include <map>
#include "csc/csc.hpp"
#include "csc/alias.hpp"

struct Dpair;
struct Ddomain;
using DpairPtr = std::shared_ptr<Dpair>;
using DdomainPtr = std::shared_ptr<Ddomain>;
using DpairWkr = std::weak_ptr<Dpair>;
using DdomainWkr = std::weak_ptr<Ddomain>;

using str = CscStr;
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
    CscStr name;
    CscStr value;
    DpairPtr next;
    DpairWkr prev;
};

struct Ddomain{
    CscStr name;
    DpairPtr pairs;
    DdomainPtr child;
    DdomainPtr next;
    DdomainWkr parent;
    DdomainWkr prev;
};
#endif

#endif