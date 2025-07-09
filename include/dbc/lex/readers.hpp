#ifndef DBC_READERS_HPP
#define DBC_READERS_HPP

#include "dbc/dbc.hpp"
#include "dbc/lex/TokenReader.hpp"
DBC_BEGIN

class EmptyReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(DbcChar ch) const noexcept override;
    bool canRead(DbcChar ch) const noexcept override;
    void readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept override;
};

class UnknownReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(DbcChar ch) const noexcept override;
    bool canRead(DbcChar ch) const noexcept override;
    void readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept override;
};

class BlankReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(DbcChar ch) const noexcept override;
    bool canRead(DbcChar ch) const noexcept override;
    void readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept override;
};

class StringReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(DbcChar ch) const noexcept override;
    bool canRead(DbcChar ch) const noexcept override;
    void readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept override;

protected:
    virtual DbcChar escape(DbcChar ch) const noexcept;
};

class OperatorReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(DbcChar ch) const noexcept override;
    bool canRead(DbcChar ch) const noexcept override;
    void readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept override;
};

DBC_END
#endif