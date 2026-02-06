#ifndef CSC_CORE_TYPES_HPP
#define CSC_CORE_TYPES_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

/* 此别名模板提供给getArray*系列函数使用，用于将类型Tp映射为std::vector<Tp> */
template<typename Tp>
using ArrayTp = std::vector<Tp>;

CSC_END
#endif