#include "csc/lex/PureLexer.hpp"
#include "csc/lex/readers.hpp"
CSC_BEGIN

PureLexer::PureLexer() : m_autoSkipBlank(true){
    installReaders();
    installConverters();
}

LexResult PureLexer::nextResultFrom(CharMngr &mngr){
    LexResult result{LexHint::OK};
    Size_t idx = 0;

    while(mngr.valid() && idx < m_readers.size()){
        /* 检查reader是否可用于读取下一个字符 */
        auto &reader = m_readers.at(idx);
        if(!(reader -> readable(mngr))){
            ++idx; 
            continue;
        }

        /* 读取token，然后根据token类型和选项设置hint字段 */
        result.token = reader -> read(mngr);
        setHint(result);

        if(result.hint == LexHint::Ignored){
            idx = 0;
            continue;
        }

        /* 为Identifier类型的token转换type字段 */
        identifierConverter(result.token);
        return result;
    }

    /* 如果已遍历完string，则放弃读取 */
    if(!mngr.valid()){
        return LexResult{LexHint::Aborted};
    }

    /* 如果string还有剩余内容，并且没有任何reader可读取，则视为未知token */
    result.token.type = TokenType::Unknown;
    return result;
}

void PureLexer::setHint(LexResult &result) const{
    /* 对于注释和空白(autoSkipBlank为true时)，设置hint字段为Ignored */
    if(result.token.type == TokenType::Description){
        result.hint = LexHint::Ignored;
    }
    else if(result.token.type == TokenType::Blank && m_autoSkipBlank){
        result.hint = LexHint::Ignored;
    }
}

void PureLexer::setAutoSkipBlank(bool b){
    m_autoSkipBlank = b;
}

void PureLexer::identifierConverter(Token &token){
    /* 对于不是Identier的token，直接返回*/
    if(token.type != TokenType::Identifier) return;

    /* 从map中根据token.str找到对应的映射TokenType，然后修改token的type字段 */
    auto pos = m_converters.find(token.str);
    if(pos == m_converters.end()) return;
    token.type = pos -> second;
}

void PureLexer::installReaders(){
    m_readers.push_back(std::make_shared<BlankReader>());
    m_readers.push_back(std::make_shared<IdentifierReader>());
    m_readers.push_back(std::make_shared<OperatorReader>());
    m_readers.push_back(std::make_shared<NumberReader>());
    m_readers.push_back(std::make_shared<DescriptionReader>());
    m_readers.push_back(std::make_shared<StringReader>());
    m_readers.push_back(std::make_shared<ArrayReader>());
}

void PureLexer::installConverters(){
    m_converters.insert({KW_TRUE, TokenType::Keyword});
    m_converters.insert({KW_FALSE, TokenType::Keyword});
    m_converters.insert({KW_ACTION, TokenType::Keyword});
}

CSC_END