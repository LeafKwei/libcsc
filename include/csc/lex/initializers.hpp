#ifndef CSC_LEX_INITIALIZERS_HPP
#define CSC_LEX_INITIALIZERS_HPP

#include "csc/lex/types.hpp"
#include "csc/lex/readers.hpp"
#include "csc/lex/InitAgent.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

/* 推荐使用xxxlexer_initializer的命名形式对Lexer的初始化函数命名 */
inline void stdlexer_initializer(PureLexer &lexer){
    InitAgent agent;

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

CSC_END
#endif