#ifndef DBC_LEXER_HPP
#define DBC_LEXER_HPP

#include <functional>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"

DBC_BEGIN

enum class CharType{Empty, Operator, Blank, Other};
const char *operatorAssign = "=";
const char *operatorDomain = "::";
const char *operatorDescribe = ";";
const char *operatorQuota = "\"";
const char *operatorQuotas = "\"\"\"";

class LexHelper{
public:
    LexHelper() noexcept;
    ~LexHelper();

   DbcString readToken(const DbcString &raw);
   DbcString readToken(const DbcString &raw, std::function<bool(DbcChar)> decider);


private:
    int m_nextIndex;
    int m_rowCounter;
    int m_colCounter;
    CharType m_lastCharType;

    CharType recognizeChar(DbcChar ch);
};

DBC_END
#endif