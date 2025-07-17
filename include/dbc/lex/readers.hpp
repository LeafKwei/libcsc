#ifndef DBC_READERS_HPP
#define DBC_READERS_HPP

#include "dbc/dbc.hpp"
#include "dbc/lex/TokenReader.hpp"
DBC_BEGIN

class EmptyReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(Dchar ch) const noexcept override;
    bool canRead(Dchar ch) const noexcept override;
    void readToken(const Dstring &raw, Dstring &buffer, Locator &locator) const noexcept override;
};

class UnknownReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(Dchar ch) const noexcept override;
    bool canRead(Dchar ch) const noexcept override;
    void readToken(const Dstring &raw, Dstring &buffer, Locator &locator) const noexcept override;
};

class BlankReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(Dchar ch) const noexcept override;
    bool canRead(Dchar ch) const noexcept override;
    void readToken(const Dstring &raw, Dstring &buffer, Locator &locator) const noexcept override;
};

class StringReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(Dchar ch) const noexcept override;
    bool canRead(Dchar ch) const noexcept override;
    void readToken(const Dstring &raw, Dstring &buffer, Locator &locator) const noexcept override;

protected:
    virtual Dchar escape(Dchar ch) const noexcept;
};

class OperatorReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(Dchar ch) const noexcept override;
    bool canRead(Dchar ch) const noexcept override;
    void readToken(const Dstring &raw, Dstring &buffer, Locator &locator) const noexcept override;
};

DBC_END
#endif