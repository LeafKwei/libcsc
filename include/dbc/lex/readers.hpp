#ifndef DBC_LEX_READERS_HPP
#define DBC_LEX_READERS_HPP

#include "dbc/dbc.hpp"
#include "dbc/lex/TokenReader.hpp"
DBC_BEGIN

class EmptyReader : public TokenReader{
public:
    Token readToken(CharPicker &picker) const noexcept override;
protected:
    virtual inline bool canRead(Dchar ch) const noexcept;
    virtual inline bool isThisReader(CharPicker &picker) const noexcept;
};

class UnknownReader : public EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override;
};

class BlankReader : public EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

class IdentifierReader : public EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

class NumberReader : public EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

class StringReader : public EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

class LongStringReader : public EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

class OperatorReader : public EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

class DelimitorReader : public EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

DBC_END
#endif