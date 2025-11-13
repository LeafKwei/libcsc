/*
#include <cstdio>
#include <iostream>
#include <fstream>
#include "csc/lex/CharMngr.hpp"
#include "csc/lex/functions.hpp"
#include "csc/lex/initializers.hpp"
#include "csc/lex/Locator.hpp"
#include "csc/lex/Lexer.hpp"
#include "csc/lex/PureLexer.hpp"
using namespace csc;

void show(const LexResult &result){
    if(result.hint == LexHint::Aborted) {printf("Reached end\n"); return; }
    switch(result.token.type){
        case TokenType::Blank:
            printf("Blank: %s\n", result.token.str.c_str());
            break;
        case TokenType::Identifier:
            printf("Identifier: %s\n", result.token.str.c_str());
            break;
        case TokenType::Operator:
            printf("Operator: %s\n", result.token.str.c_str());
            break;
        case TokenType::Number:
            printf("Number: %s\n", result.token.str.c_str());
            break;
        case TokenType::String:
            printf("String: %s\n", result.token.str.c_str());
            break;
        case TokenType::Array:
             printf("Array: %s\n", result.token.str.c_str());
             break;
        case TokenType::Keyword:
            printf("Keyword: %s\n", result.token.str.c_str());
            break;
        default:
            printf("Unexepted token-type: %d\n", static_cast<int>(result.token.type));
            break;
    }
}

int main(void){
    std::ifstream ifs("myconfig.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());  //Use parentheses for (std::istreambuf_iterator<char>(ifs) because cpp compiler will recongnize it as a function declaraion without parentheses

#if 0
    Lexer lexer{};
    lexer.setAutoSkipBlank(true);

    while(lexer.valid()){
        auto token = lexer.nextResult();
        if(token.type == TokenType::Unknown){
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
    stdlexer_initializer(pure);
    //pure.setAutoSkipBlank(false);
    CharMngr mngr{str};

    while(mngr.valid()){
        auto result = pure.nextResultFrom(mngr);
        if(result.hint == LexHint::Aborted) break;
        if(result.token.type == TokenType::Unknown){
            Locator locator(mngr.str(), mngr.index());
            printf("Unexcepted error at row: %d, col: %d\n", locator.row(), locator.col());
            printf("str: `%s`\n", mngr.str().c_str() + locator.index());
            printf("token: `%s`\n", result.token.str.c_str());
            break;
        }

        show(result);
    }

#endif
}
*/