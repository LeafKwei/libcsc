#ifndef CSC_ALIAS_HPP
#define CSC_ALIAS_HPP

#include "csc/csc.hpp"
#include <string>
#include <map>
CSC_BEGIN

//===================== Alias ===================
using CscChar = char;
using CscStr = std::string;
using ConstStr = const CscStr&;
using UID = unsigned long long;     //U means unique.
using size_t = std::size_t;

CSC_END
#endif