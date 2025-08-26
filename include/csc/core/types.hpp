#ifndef CSC_CORE_TYPES_HPP
#define CSC_CORE_TYPES_HPP

#include <vector>
#include <memory>
#include <map>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

using bools = std::vector<bool>;
using ints = std::vector<int>;
using longs = std::vector<long>;
using doubles = std::vector<double>;
using strings = std::vector<CscStr>;

CSC_END
#endif