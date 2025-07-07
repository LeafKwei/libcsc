#ifndef DBC_STRUCTS_HPP
#define DBC_STRUCTS_HPP

#include <functional>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/lex/lex.hpp"

DBC_BEGIN

struct UpdatePack{
    TokenType type;
    int index;
    int row;
    int col;

    UpdatePack() : type(TokenType::Empty), index(0), row(0), col(0){}

    explicit UpdatePack(TokenType type, int index, int row, int col){
        this -> type = type;
        this -> index = index;
        this -> row = row;
        this -> col = col;
    }
};

struct OptionBranch{
    using OptionHandler = std::function<void(DbcChar, DbcString&, UpdatePack&, TokenType, TokenType)>;

    Option option;
    OptionHandler handler;

    explicit OptionBranch(Option option, OptionHandler handler){
        this -> option = option;
        this -> handler = handler;
    }
};

struct TokenTypeBranch
{
    DbcChar ch;
    TokenType type;

    explicit TokenTypeBranch(DbcChar ch, TokenType type) noexcept{
        this -> ch = ch;
        this -> type = type;
    }
};

DBC_END
#endif