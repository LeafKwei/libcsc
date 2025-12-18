#ifndef CSC_CONTEXT_VAL_HPP
#define CSC_CONTEXT_VAL_HPP

#include "csc/lex/types.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

ValueType valueTypeof(const Token &token);
Value makeValueFrom(const Token &token, ValueType type);
Value makeZeroValue(ValueType type);
String valueToString(const Value &value, ValueType type);

CSC_END
#endif