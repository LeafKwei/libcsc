#include "csc/lex/TokenPool.hpp"
CSC_BEGIN

TokenPool::TokenPool(){
    initIgnoredToken();
    initConvToken();
}

void TokenPool::addToken(const Token &token){
    if(isIgnoredToken(token.type)) return;           //如果此token是被忽略的token类型，则不添加
    TokenPtr tp = std::make_shared<Token>();
    (*tp) = token;
    convertTokenType(*tp);
    appendToken(tp);
}

void TokenPool::addToken(Token &&token){
    if(isIgnoredToken(token.type)) return;
    TokenPtr tp = std::make_shared<Token>();
    (*tp) = std::move(token);
    convertTokenType(*tp);
    appendToken(tp);
}

TokenHolder TokenPool::nextHolder(){
    TokenHolder holder;
    if(tokens_.empty()) return holder;
    
    /* 如果是数组等具有复数个元素的token  */
    if(isPuralToken((*tokens_.front()))){
        todo
        return holder;
    }

    return holder;
}

bool TokenPool::empty() const noexcept{
    return tokens_.empty();
}

Size_t TokenPool::size() const noexcept{
    return tokens_.size();
}

void TokenPool::initIgnoredToken(){
    ignored_.insert(TokenType::Blank);
    ignored_.insert(TokenType::Description);
    ignored_.insert(TokenType::Separator);
}

void TokenPool::initConvToken(){
    conv_.insert({"true", TokenType::Keyword});
    conv_.insert({"false", TokenType::Keyword});
    conv_.insert({"action", TokenType::Keyword});
}

void TokenPool::initPluralRule(){
    rule_.push_back({Token{"[", TokenType::Limitor}, Token{"]", TokenType::Limitor}});
    rule_.push_back({Token{"(", TokenType::Limitor}, Token{")", TokenType::Limitor}});
    rule_.push_back({Token{"{", TokenType::Limitor}, Token{"}", TokenType::Limitor}});
}

void TokenPool::appendToken(const TokenPtr &ptr){
    tokens_.push_back(ptr);
}

bool TokenPool::isIgnoredToken(TokenType type){
    return ignored_.find(type) != ignored_.end();
}

void TokenPool::convertTokenType(Token &token){
    auto pos = conv_.find(token.str);
    if(pos == conv_.end()) return;
    token.type = pos -> second;
}

bool TokenPool::isPuralToken(const Token &token){
    for(const auto &rule : rule_){
        if(rule.first.str == token.str && rule.first.type == token.type){  //如果接下来要读取的token是数组一类的具有复数个元素的token
            return true;
        }
    }

    return false;
}

CSC_END