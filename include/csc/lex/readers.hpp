#ifndef CSC_LEX_READERS_HPP
#define CSC_LEX_READERS_HPP

#include <functional>
#include "csc/alias.hpp"
#include "csc/lex/CharMngr.hpp"
#include "csc/lex/TokenReader.hpp"
CSC_BEGIN

////////////////////////////////////////////////////////////////////////////////////////
inline void default_initor(Any &local) noexcept{}
inline void default_fintor(Any &local) noexcept{}
////////////////////////////////////////////////////////////////////////////////////////

CSC_END
#endif