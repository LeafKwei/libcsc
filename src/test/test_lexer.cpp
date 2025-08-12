#include <cstdio>
#include <iostream>
#include <fstream>
#include "dbc/lex/CharMngr.hpp"
#include "dbc/lex/functions.hpp"
#include "dbc/lex/Locator.hpp"
#include "dbc/core/Dcontext.hpp"
#include "dbc/lex/Lexer.hpp"
using namespace dbc;

void show(const Token &token){
    switch(token.type){
        case TokenType::Aborted:
            printf("Reached end\n");
            break;
        case TokenType::Blank:
            printf("Blank: %s\n", token.buffer.c_str());
            break;
        case TokenType::Identifier:
            printf("Identifier: %s\n", token.buffer.c_str());
            break;
        case TokenType::Operator:
            printf("Operator: %s\n", token.buffer.c_str());
            break;
        case TokenType::Number:
            printf("Number: %s\n", token.buffer.c_str());
            break;
        case TokenType::String:
            printf("String: %s\n", token.buffer.c_str());
            break;
        default:
            printf("Unexepted\n");
            break;
    }
}

int main(void){
    Lexer lexer("        _uname_ = \"Hello \\n World\"    _name = 0x10ABCDEF   _val987 = 9899 _val2 = 887.445\n\n  ;;;;;I am a description \nHacker_89_998__ = 19930.113   Priority    =     0xFF89E  ");
    lexer.setAutoSkipBlank(true);

    while(lexer.valid()){
        auto token = lexer.nextToken();
        if(token.type == TokenType::Unexcepted){
            auto locator = lexer.locator();
            printf("Unexcepted error at col: %d, row: %d\n", locator.col(), locator.row());
            printf("str: `%s`\n", lexer.str().c_str() + locator.index());
            break;
        }

        show(token);
    }
}