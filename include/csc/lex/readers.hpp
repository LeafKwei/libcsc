#ifndef CSC_LEX_READERS_HPP
#define CSC_LEX_READERS_HPP

#include <vector>
#include <memory>
#include "csc/lex/TokenReader.hpp"
CSC_BEGIN

class CommonReader : public TokenReader{
public:
    bool readable(CharMngr &mngr) override;
    Token read(CharMngr &mngr) override;
    TokenType type() override;

protected:
    virtual bool canRead(CscChar ch);
};

class BlankReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;
};

class DescriptionReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;
};

class IdentifierReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;
};

class OperatorReader: public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;
};

class NumberReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    Token read(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;

private:
    int m_num;        //Realy reading number of character.
    int m_type;        //0 int/float, 1 hex

    void readPrefix(Token &token, CharMngr &mngr);
    void readHex(Token &token, CharMngr &mngr);
    void readNumber(Token &token, CharMngr &mngr);
};

class StringReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    Token read(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;

private:
    void readString(Token &token, CharMngr &mngr);
};

class ArrayReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    Token read(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(CscChar ch) override;
};


CSC_END
#endif