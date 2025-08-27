#ifndef CSC_CORE_TYPES_HPP
#define CSC_CORE_TYPES_HPP

#include <vector>
#include <memory>
#include <map>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

using array_bool = std::vector<bool>;
using array_int    = std::vector<int>;
using array_long = std::vector<long>;
using array_double = std::vector<double>;
using array_string = std::vector<CscStr>;

CSC_END
#endif