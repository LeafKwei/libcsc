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
}

void TokenPool::initConvToken(){
    conv_.insert({"true", TokenType::Keyword});
    conv_.insert({"false", TokenType::Keyword});
    conv_.insert({"action", TokenType::Keyword});
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

CSC_END