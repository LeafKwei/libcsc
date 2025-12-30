#ifndef CSC_UTILITY_HPP
#define CSC_UTILITY_HPP

#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
CSC_BEGIN

////////////////////////////////////////////////////////////////////////////////////////类型定义
using Rowcol = std::pair<Offset_t, Offset_t>; //pair<行号, 列号>

////////////////////////////////////////////////////////////////////////////////////////函数声明
String toEscapingString(const String &str);
Rowcol locateFrom(const String &str, Offset_t offset);


CSC_END
#endif