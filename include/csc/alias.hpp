#ifndef CSC_ALIAS_HPP
#define CSC_ALIAS_HPP

#include <any>
#include <string>
#include <cstdint>
#include "csc/csc.hpp"
CSC_BEGIN

 /* 声明一些通用的别名 */

//===================== Alias ===================
using Char = char;
using String = std::string;
using UID = unsigned long long;     //U means unique.
using Size_t = std::size_t;
using Index_t = int32_t;
using Offset_t = int32_t;
using Any = std::any;

CSC_END
#endif