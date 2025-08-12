#ifndef DBC_LEX_FUNCIONS_HPP
#define DBC_LEX_FUNCIONS_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

inline bool isAlpha(Dchar ch) noexcept{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

inline bool isNumber(Dchar ch) noexcept{
    return (ch >= '0' && ch <= '9');
}

inline bool isHexNumber(Dchar ch) noexcept{
    return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <='F');
}

inline bool isUnvisible(Dchar ch) noexcept{
    return ch <= 32;
}

inline bool isNewLine(Dchar ch) noexcept{
    return ch == '\n';
}

inline bool isEscape(Dchar ch) noexcept{
    return ch == '\\';
}

inline bool isDot(Dchar ch) noexcept{
    return ch == '.';
}

inline bool isBlank(Dchar ch) noexcept{
    return (ch == '\n') || (ch == '\t' || (ch == ' '));
}

inline bool isIdentifier(Dchar ch) noexcept{
    return isAlpha(ch) || isNumber(ch) || ch == '_';
}

inline bool isOperator(Dchar ch) noexcept{
    switch(ch){
        case ':' :
        case '=':
            return true;
        default:
            return false;
    }
}

inline bool isDelimitor(Dchar ch) noexcept{
    switch(ch){
        case '\'':
        case '\"':
        case '[':
        case ']':
        case ',':
            return true;
        default:
            return false;
    }
}

inline Dchar escapeTo(Dchar ch) noexcept{
    switch(ch){
        case '0':
            return '\0';
        case 't':
            return '\t';
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 'b':
            return '\b';
        default:
            return ch;
    }
}

DBC_END
#endif