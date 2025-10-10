#ifndef CSC_LEX_READERS_HPP
#define CSC_LEX_READERS_HPP

#include <vector>
#include <memory>
#include "csc/lex/TokenReader.hpp"
CSC_BEGIN

class CommonReader : public TokenReader{
public:
    bool          readable(CharMngr &mngr) override;
    Token        read(CharMngr &mngr) override;
    TokenType type() override;

protected:
    virtual bool      canRead(Char ch);
};

class BlankReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Char ch) override;
};

class DescriptionReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Char ch) override;
};

class IdentifierReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Char ch) override;
};

class OperatorReader: public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Char ch) override;
};

class NumberReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    Token read(CharMngr &mngr) override;
    TokenType type() override;

private:
    int m_num;        //实际读取的数字字符个数
    int m_type;        //0表示整型、浮点型，1表示十六进制

    void readPrefix(Token &token, CharMngr &mngr);
    void readHex(Token &token, CharMngr &mngr);
    void readNumber(Token &token, CharMngr &mngr);
};

class StringReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    Token read(CharMngr &mngr) override;
    TokenType type() override;

private:
    void readString(Token &token, CharMngr &mngr);
};

class ArrayReader : public CommonReader{
public:
    bool readable(CharMngr &mngr) override;
    Token read(CharMngr &mngr) override;
    TokenType type() override;
};


CSC_END
#endif