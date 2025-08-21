#ifndef DBC_CORE_TYPES_HPP
#define DBC_CORE_TYPES_HPP

#include <vector>
#include <memory>
#include <map>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

using str = Dstring;
using barray = std::vector<bool>;
using iarray = std::vector<int>;
using larray = std::vector<long>;
using darray = std::vector<double>;
using sarray = std::vector<str>;

DBC_END
#endif