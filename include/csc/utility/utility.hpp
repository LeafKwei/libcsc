#ifndef CSC_UTILITY_HPP
#define CSC_UTILITY_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/lex/types.hpp"
#include "csc/syntax/types.hpp"
#include "csc/core/types.hpp"

CSC_BEGIN

String join(String splitor, const std::vector<String> &elements, const std::initializer_list<String> &filters={});
int      baseOf(crString str);
String toEscapingString(crString str);

CSC_END
#endif