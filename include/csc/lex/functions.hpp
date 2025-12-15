#ifndef CSC_LEX_FUNCTIONS_HPP
#define CSC_LEX_FUNCTIONS_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

inline bool isAlpha(Char ch) noexcept{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

inline bool isNumber(Char ch) noexcept{
    return (ch >= '0' && ch <= '9');
}

inline bool isHexNumber(Char ch) noexcept{
    return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <='F') || (ch >= 'a' && ch <= 'f');
}

inline bool isUnvisible(Char ch) noexcept{
    return ch <= 32;
}

inline bool isNewLine(Char ch) noexcept{
    return ch == '\n';
}

inline bool isEscape(Char ch) noexcept{
    return ch == '\\';
}

inline bool isDot(Char ch) noexcept{
    return ch == '.';
}

inline bool isBlank(Char ch) noexcept{
    return (ch == '\n') || (ch == '\t' || (ch == ' '));
}

inline bool isIdentifier(Char ch) noexcept{
    return isAlpha(ch) || isNumber(ch) || ch == '_';
}

inline bool isOperator(Char ch) noexcept{
    switch(ch){
        case ':'   :
        case '=' :
            return true;
        default:
            return false;
    }
}

inline bool isLimitor(Char ch) noexcept{
    switch(ch){
        case '{'   :
        case '}'   :
        case '('   :
        case ')'   :
        case '['   :
        case ']'   :
            return true;
        default:
            return false;
    }
}

inline bool isSeparator(Char ch) noexcept{
    switch(ch){
        case ',' :
            return true;
        default:
            return false;
    }
}

inline Char escapeTo(Char ch) noexcept{
    switch(ch){
        case '0' :
            return '\0';
        case 't' :
            return '\t';
        case 'n' :
            return '\n';
        case 'r' :
            return '\r';
        case 'b' :
            return '\b';
        default:
            return ch;
    }
}

CSC_END
#endif