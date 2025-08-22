#ifndef CSC_LEX_FUNCIONS_HPP
#define CSC_LEX_FUNCIONS_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

inline bool isAlpha(CscChar ch) noexcept{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

inline bool isNumber(CscChar ch) noexcept{
    return (ch >= '0' && ch <= '9');
}

inline bool isHexNumber(CscChar ch) noexcept{
    return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <='F');
}

inline bool isUnvisible(CscChar ch) noexcept{
    return ch <= 32;
}

inline bool isNewLine(CscChar ch) noexcept{
    return ch == '\n';
}

inline bool isEscape(CscChar ch) noexcept{
    return ch == '\\';
}

inline bool isDot(CscChar ch) noexcept{
    return ch == '.';
}

inline bool isBlank(CscChar ch) noexcept{
    return (ch == '\n') || (ch == '\t' || (ch == ' '));
}

inline bool isIdentifier(CscChar ch) noexcept{
    return isAlpha(ch) || isNumber(ch) || ch == '_';
}

inline bool isOperator(CscChar ch) noexcept{
    switch(ch){
        case ':'   :
        case '=' :
            return true;
        default:
            return false;
    }
}

inline bool isDelimitor(CscChar ch) noexcept{
    switch(ch){
        case '\''  :
        case '\"' :
        case '{'   :
        case '}'   :
            return true;
        default:
            return false;
    }
}

inline bool isSeparator(CscChar ch) noexcept{
    switch(ch){
        case ',' :
            return true;
        default:
            return false;
    }
}

inline CscChar escapeTo(CscChar ch) noexcept{
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