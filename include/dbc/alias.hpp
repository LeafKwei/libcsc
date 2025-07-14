#ifndef DBC_ALIAS_HPP
#define DBC_ALIAS_HPP

#include "dbc/dbc.hpp"
#include <string>
#include <map>
DBC_BEGIN

//===================== Alias ===================
using DbcChar = char;
using DbcString = std::string;
using DbcKey = const DbcString;
using DbcPair = std::pair<DbcString,DbcString>;


DBC_END
#endif