#ifndef CSC_CORE_TYPES_HPP
#define CSC_CORE_TYPES_HPP

#include <vector>
#include <memory>
#include <map>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

using str = CscStr;
using barray = std::vector<bool>;
using iarray = std::vector<int>;
using larray = std::vector<long>;
using darray = std::vector<double>;
using sarray = std::vector<str>;

CSC_END
#endif