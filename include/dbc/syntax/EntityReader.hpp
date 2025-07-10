#ifndef DBC_ENTITY_READER
#define DBC_ENTITY_READER

#include <vector>
#include "dbc/dbc.hpp"
#include "dbc/lex/LexHelper.hpp"
#include "dbc/core/DbcDomain.hpp"
DBC_BEGIN

using Condition = Token;

class EntityReader{
public:
    bool isThisType(const std::vector<Token> tokens) const noexcept;
    DbcError readEntity(const std::vector<Token> tokens, const DbcString &raw, DbcDomain &domain, LexHelper &helper) const noexcept;
};

DBC_END
#endif