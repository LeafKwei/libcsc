#ifndef CSC_LEX_READERS_HPP
#define CSC_LEX_READERS_HPP

#include <vector>
#include <memory>
#include "csc/lex/TokenReader.hpp"
CSC_BEGIN

class CommonReader : public TokenReader{
public:
    Token read(CharMngr &mngr) override;
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    virtual bool canRead(CscChar ch);
};

class BlankReader : public CommonReader{
public:
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;
};

class DescriptionReader : public CommonReader{
public:
    Token read(CharMngr &mngr) override;
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;
};

class IdentifierReader : public CommonReader{
public:
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;
};

class OperatorReader: public CommonReader{
public:
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;
};

class NumberReader : public CommonReader{
public:
    Token read(CharMngr &mngr) override;
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;

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
    bool canRead(CscChar ch) override;

private:
    void readString(Token &token, CharMngr &mngr);
};

class ArrayReader : public CommonReader{
public:
    Token read(CharMngr &mngr) override;
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;

private:
    void trim(Token &token);
    bool isValue(const Token &token);
};


CSC_END
#endif