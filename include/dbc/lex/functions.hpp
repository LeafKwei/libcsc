#ifndef DBC_LEX_FUNCIONS_HPP
#define DBC_LEX_FUNCIONS_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

inline bool isAlpha(Dchar ch){
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

inline bool isUnvisible(Dchar ch){
    return ch <= 32;
}

inline bool isBlank(Dchar ch){
    return (ch == '\n') || (ch == '\t' || (ch == ' '));
}

inline bool isNewLine(Dchar ch){
    return ch == '\n';
}

inline bool isNumber(Dchar ch){
    return (ch >= '0' && ch <= '9');
}

inline bool isDot(Dchar ch){
    return ch == '.';
}

inline bool isQuota(Dchar ch){
    return (ch == '\'' || ch == '\"');
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

DBC_END
#endif