#ifndef CSC_SYNTAX_OPR_HPP
#define CSC_SYNTAX_OPR_HPP

#include "csc/alias.hpp"
#include "csc/syntax/types.hpp"
CSC_BEGIN

String genKeyFrom(OperandType type, const String &str);
OperandType operandTypeOf(const Token &token);

CSC_END
#endif