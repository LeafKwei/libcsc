#ifndef DBC_ALIAS_HPP
#define DBC_ALIAS_HPP

#include "dbc.hpp"
#include "core/DbcResult.hpp"
#include <string>

DBC_BEGIN

//===================== Alias ===================
using DbcString = std::string;
using DbcKey = const std::string&;
using DbcValue = DbcResult;

DBC_END
#endif