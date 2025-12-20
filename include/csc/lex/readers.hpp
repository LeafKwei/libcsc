#ifndef CSC_LEX_READERS_HPP
#define CSC_LEX_READERS_HPP

#include "csc/alias.hpp"
#include "csc/lex/functions.hpp"
#include "csc/lex/CharMngr.hpp"
#include "csc/lex/TokenReader.hpp"
CSC_BEGIN

////////////////////////////////////////////////////////////////////////////////////////
inline void default_initor(Any &local) noexcept{}
inline void default_fintor(Any &local) noexcept{}

////////////////////////////////////////////////////////////////////////////////////////Blank
inline bool blank_readable(CharMngr &mngr, Any &local){
    return isBlank(mngr.getch());
}

inline TokenPair blank_read(CharMngr &mngr, Any &local){
    while(mngr.valid()){
        if(!isBlank(mngr.getch())){
            break;
        }

        mngr.forward();
    }

    return TokenPair{RdErrno::OK, Token{"", TokenType::Blank}};
}

////////////////////////////////////////////////////////////////////////////////////////Description
inline bool description_readable(CharMngr &mngr, Any &local){
    return (mngr.getch() == ';');
}

inline TokenPair description_read(CharMngr &mngr, Any &local){
    while(mngr.valid()){
        if(isNewLine(mngr.forward())){
            break;
        }
    }

    return TokenPair{RdErrno::OK, Token{"", TokenType::Description}}; 
}

////////////////////////////////////////////////////////////////////////////////////////Limitor
inline bool limitor_readable(CharMngr &mngr, Any &local){
    return (isLimitor(mngr.getch()));
}

inline TokenPair limitor_read(CharMngr &mngr, Any &local){
    TokenPair pair{RdErrno::OK, Token{"", TokenType::Limitor}};

    while(mngr.valid()){
        auto ch = mngr.getch();

        if(!isLimitor(ch)){
            break;
        }

        pair.second.str.push_back(ch);
        mngr.forward();
    }

    return pair;
}

////////////////////////////////////////////////////////////////////////////////////////Separator
inline bool separator_readable(CharMngr &mngr, Any &local){
    return (isSeparator(mngr.getch()));
}

inline TokenPair separator_read(CharMngr &mngr, Any &local){
    TokenPair pair{RdErrno::OK, Token{"", TokenType::Separator}};

    while(mngr.valid()){
        auto ch = mngr.getch();

        if(!isSeparator(ch)){
            break;
        }

        pair.second.str.push_back(ch);
        mngr.forward();
    }

    return pair;
}

////////////////////////////////////////////////////////////////////////////////////////Identifier
inline bool identifier_readable(CharMngr &mngr, Any &local){
    return (isAlpha(mngr.getch()) || mngr.getch() == '_');
}

inline TokenPair identifier_read(CharMngr &mngr, Any &local){
    TokenPair pair{RdErrno::OK, Token{"", TokenType::Identifer}};

    while(mngr.valid()){
        auto ch = mngr.getch();
        if(!isIdentifier(ch)){
            break;
        }

        pair.second.str.push_back(ch);
        mngr.forward();
    }

    return pair;
}

////////////////////////////////////////////////////////////////////////////////////////Operator
inline bool operator_readable(CharMngr &mngr, Any &local){
    return (isOperator(mngr.getch()));
}

inline TokenPair operator_read(CharMngr &mngr, Any &local){
    TokenPair pair{RdErrno::OK, Token{"", TokenType::Operator}};

    while(mngr.valid()){
        auto ch = mngr.getch();
        if(!isOperator(ch)){
            break;
        }

        pair.second.str.push_back(ch);
        mngr.forward();
    }

    return pair;
}

////////////////////////////////////////////////////////////////////////////////////////Number
struct number_local{
    bool hex;
    bool real;
    bool sign;
};

inline void number_initor(Any &local){
    number_local load{};
    local = load;
}

inline bool number_testHex(CharMngr &mngr, number_local &local){
    if(mngr.surplus() >= 2){
        if(mngr.near(0) == '0' && mngr.near(1) == 'x'){    //如果存在前缀0x
            local.hex = true;
            return true;
        }
    }

    return false;
}

inline bool number_testSign(CharMngr &mngr, number_local &local){
    if(mngr.surplus() >= 2){
        if((mngr.near(0) == '+' || mngr.near(0) == '-') && isNumber(mngr.near(1))){
            local.sign = true;
            return true;
        }
    }

    return false;
}

inline bool number_testNormal(CharMngr &mngr, number_local &local){
    return (isNumber(mngr.getch()));
}

inline bool number_readable(CharMngr &mngr, Any &local){
    auto &load = std::any_cast<number_local&>(local);
    return ( (number_testHex(mngr, load) || number_testNormal(mngr, load)) || (number_testSign(mngr, load)));  //hex需要首先检测，避免其前缀0x被识别为普通数字
}

inline void number_hex(CharMngr &mngr, number_local &local, TokenPair &pair){
    pair.second.type = TokenType::HexInteger;
    pair.second.str.insert(0, "0x");
    mngr.seek(CharMngr::Cur, 2); //跳过0x

    while(mngr.valid()){
        auto ch = mngr.getch();
        if(!isHexNumber(ch)){
            break;
        }

        pair.second.str.push_back(ch);
        mngr.forward();
    }
}

inline void number_else(CharMngr &mngr, number_local &local, TokenPair &pair){
    if(local.sign){
        pair.second.str.push_back(mngr.forward());  //压入符号
    }

    while(mngr.valid()){
        auto ch = mngr.getch();
        if(ch == '.'){
            if(local.real){  //如果一个数字中出现了两个点
                pair.first = RdErrno::Format;
                return;
            }

            local.real = true;
            pair.second.type = TokenType::Float;
            pair.second.str.push_back('.');
            mngr.forward();
            continue;
        }

        if(!isNumber(ch)){
            break;
        }

        pair.second.str.push_back(ch);
        mngr.forward();
    }
}

inline TokenPair number_read(CharMngr &mngr, Any &local){
    TokenPair pair{RdErrno::OK, Token{"", TokenType::Integer}};
    auto &load = std::any_cast<number_local&>(local);

    if(load.hex){
        number_hex(mngr, load, pair);
    }
    else{
        number_else(mngr, load, pair);
    }

    return pair;
}

////////////////////////////////////////////////////////////////////////////////////////String
inline bool string_readable(CharMngr &mngr, Any &local){
    return (mngr.getch() == '"');
}

inline TokenPair string_read(CharMngr &mngr, Any &local){
    TokenPair pair{RdErrno::OK, Token{"", TokenType::String}};
    mngr.forward();     //跳过引号

    bool escape = false;
    while(mngr.valid()){
        auto ch = mngr.getch();

        if(escape){
            escape = false;
            pair.second.str.push_back(ch);
            mngr.forward();
            continue;
        }

        if(ch == '\\'){
            escape = true;
            mngr.forward();
            continue;
        }

        if(ch == '"'){
            mngr.forward();
            break;
        }

        pair.second.str.push_back(ch);
        mngr.forward();
    }

    return pair;
}

CSC_END
#endif