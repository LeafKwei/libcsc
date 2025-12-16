#ifndef CSC_CONTEXT_VALTOOL_HPP
#define CSC_CONTEXT_VALTOOL_HPP

#include "csc/lex/types.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

ValueUnit makeValueFrom(const Token &token);
Value makeZeroValue(ValueType type);

CSC_END
#endif