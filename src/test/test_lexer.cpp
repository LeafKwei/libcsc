#include <cstdio>
#include <iostream>
#include <fstream>
#include "dbc/lex/CharMngr.hpp"
#include "dbc/lex/functions.hpp"
#include "dbc/lex/Locator.hpp"
#include "dbc/lex/Lexer.hpp"
#include "dbc/lex/PureLexer.hpp"
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
        case TokenType::Array:
             printf("Array: %s\n", token.buffer.c_str());
             break;
        case TokenType::Keyword:
            printf("Keyword: %s\n", token.buffer.c_str());
            break;
        default:
            printf("Unexepted token-type: %d\n", static_cast<int>(token.type));
            break;
    }
}

int main(void){
    std::ifstream ifs("myconfig.dbc");
    Dstring str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());  //Use parentheses for (std::istreambuf_iterator<char>(ifs) because cpp compiler will recongnize it as a function declaraion without parentheses

#if 0
    Lexer lexer{};
    lexer.setAutoSkipBlank(true);

    while(lexer.valid()){
        auto token = lexer.nextToken();
        if(token.type == TokenType::Unexcepted){
            auto locator = lexer.locator();
            printf("Unexcepted error at row: %d, col: %d\n", locator.row(), locator.col());
            printf("str: `%s`\n", lexer.str().c_str() + locator.index());
            break;
        }

        show(token);
    }
#endif

#if 1
    PureLexer pure;
    //pure.setAutoSkipBlank(false);
    CharMngr mngr{str};

    while(mngr.valid()){
        auto token = pure.nextTokenFrom(mngr);
        if(token.type == TokenType::Unexcepted){
            Locator locator(mngr.str(), mngr.index());
            printf("Unexcepted error at row: %d, col: %d\n", locator.row(), locator.col());
            printf("str: `%s`\n", mngr.str().c_str() + locator.index());
            break;
        }

        show(token);
    }

#endif
}