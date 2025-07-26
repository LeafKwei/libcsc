#ifndef DBC_LEX_READERS_HPP
#define DBC_LEX_READERS_HPP

#include "dbc/dbc.hpp"
#include "dbc/lex/TokenReader.hpp"
DBC_BEGIN

class EmptyReader : TokenReader{
public:
    Token readToken(CharPicker &picker) const noexcept override;
protected:
    virtual inline bool canRead(Dchar ch) const noexcept;
    virtual inline bool isThisReader(CharPicker &picker) const noexcept;
};

class UnknownReader : EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override;
};

class BlankReader : EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

class GeneralReader : EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

class OperatorReader : EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

class DelimitorReader : EmptyReader{
public:
    Token readToken(CharPicker &picker) const noexcept override; 
protected:
    inline bool canRead(Dchar ch) const noexcept;
    inline bool isThisReader(CharPicker &picker) const noexcept override;
};

DBC_END
#endif