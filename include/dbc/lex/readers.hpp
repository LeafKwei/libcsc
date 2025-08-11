#ifndef DBC_LEX_READERS_HPP
#define DBC_LEX_READERS_HPP

#include "dbc/lex/TokenReader.hpp"
DBC_BEGIN

class CommonReader : public TokenReader{
public:
    Token read(CharMngr &mngr) override;
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Dchar ch) override;
};

class BlankReader : public CommonReader{
public:
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
    int m_type;        //0 general, 1 hex, 2, float
    int m_directly;

    bool isGeneralNumber(CharMngr &mngr);
    bool isHexNumber(CharMngr &mngr);
};

class StringReader : public CommonReader{
public:
    bool isThisType(CharMngr &mngr) override;
    TokenType type() override;

protected:
    bool canRead(Dchar ch) override;
    bool isCompletedEnd(CharMngr &mngr) const;
};


DBC_END
#endif