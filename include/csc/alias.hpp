#ifndef CSC_ALIAS_HPP
#define CSC_ALIAS_HPP

#include "csc/csc.hpp"
#include <string>
#include <any>
CSC_BEGIN

 /* 声明一些通用的别名 */

//===================== Alias ===================
using Char = char;
using String = std::string;
using crString = const String&;
using UID = unsigned long long;     //U means unique.
using Size_t = std::size_t;
using Any = std::any;

CSC_END
#endif