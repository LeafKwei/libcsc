#ifndef DBC_LEX_READERS_HPP
#define DBC_LEX_READERS_HPP

#include <vector>
#include <memory>
#include "dbc/lex/TokenReader.hpp"
DBC_BEGIN

class CommonReader : public TokenReader{
public:
    Token read(CharMngr &mngr) override;
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    virtual bool canRead(Dchar ch);
};

class BlankReader : public CommonReader{
public:
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Dchar ch) override;
};

class DescriptionReader : public CommonReader{
public:
    Token read(CharMngr &mngr) override;
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Dchar ch) override;
};

class IdentifierReader : public CommonReader{
public:
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Dchar ch) override;
};

class OperatorReader: public CommonReader{
public:
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Dchar ch) override;
};

class NumberReader : public CommonReader{
public:
    Token read(CharMngr &mngr) override;
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Dchar ch) override;

private:
    int m_type;        //0 general, 1 float, 2 hex

    bool isHex(CharMngr &mngr);
    void readHex(Token &token, CharMngr &mngr);
    void readNumber(Token &token, CharMngr &mngr);
};

class StringReader : public CommonReader{
public:
    Token read(CharMngr &mngr) override;
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Dchar ch) override;

private:
    void readString(Token &token, CharMngr &mngr);
};

class ArrayReader : public CommonReader{
public:
    Token read(CharMngr &mngr) override;
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Dchar ch) override;

private:
    void trim(Token &token);
    bool isValueType(const Token &token);
};


DBC_END
#endif