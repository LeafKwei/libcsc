#ifndef DBC_LEX_FUNCIONS_HPP
#define DBC_LEX_FUNCIONS_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

inline bool isAlpha(Dchar ch){
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

inline bool isNumber(Dchar ch){
    return (ch >= '0' && ch <= '9');
}

inline bool isUnvisible(Dchar ch){
    return ch <= 32;
}

inline bool isNewLine(Dchar ch){
    return ch == '\n';
}

inline bool isEscape(Dchar ch){
    return ch == '\\';
}

inline bool isDot(Dchar ch){
    return ch == '.';
}

inline bool isBlank(Dchar ch){
    return (ch == '\n') || (ch == '\t' || (ch == ' '));
}

inline bool isIdentifier(Dchar ch){
    return isAlpha(ch) || ch =='_';
}

inline bool isOperator(Dchar ch){
    switch(ch){
        case ':' :
        case '=':
            return true;
        default:
            return false;
    }
}

inline bool isDelimitor(Dchar ch){
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

inline Dchar doEscape(Dchar ch){
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