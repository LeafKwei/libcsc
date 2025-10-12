#ifndef CSC_LEX_INITIALIZERS_HPP
#define CSC_LEX_INITIALIZERS_HPP

#include "csc/lex/types.hpp"
#include "csc/lex/readers.hpp"
#include "csc/lex/LexerAgent.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

/**
 * 在此文件中定义用于初始化PureLexer的函数，根据PureLexer的用途定义对应的初始化函数。
 * 推荐使用xxxlexer_initializer的命名形式对Lexer的初始化函数命名。
 */

/* 标准Lexer的初始化函数，解析csc文件时需要使用此初始化器 */
inline void stdlexer_initializer(PureLexer &lexer){
    LexerAgent agent;

    /* 添加TokenReader */
    agent.addReader(lexer, std::make_shared<BlankReader>());
    agent.addReader(lexer, std::make_shared<IdentifierReader>());
    agent.addReader(lexer, std::make_shared<OperatorReader>());
    agent.addReader(lexer, std::make_shared<NumberReader>());
    agent.addReader(lexer, std::make_shared<StringReader>());
    agent.addReader(lexer, std::make_shared<DescriptionReader>());
    agent.addReader(lexer, std::make_shared<ArrayReader>());

    /* 添加IdentifierMapper */
    agent.addMapper(lexer, KW_TRUE, TokenType::Keyword);
    agent.addMapper(lexer, KW_FALSE, TokenType::Keyword);
    agent.addMapper(lexer, KW_ACTION, TokenType::Keyword);
}

/* 解析数组token时使用此初始化器 */
inline void arraylexer_initializer(PureLexer &lexer){
    LexerAgent agent;

    /* 添加TokenReader */
    agent.addReader(lexer, std::make_shared<BlankReader>());
    agent.addReader(lexer, std::make_shared<IdentifierReader>());
    agent.addReader(lexer, std::make_shared<NumberReader>());
    agent.addReader(lexer, std::make_shared<StringReader>());

    /* 添加IdentifierMapper */
    agent.addMapper(lexer, KW_TRUE, TokenType::Keyword);
    agent.addMapper(lexer, KW_FALSE, TokenType::Keyword);
}

CSC_END
#endif