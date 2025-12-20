#include "csc/types.hpp"
#include "csc/lex/TokenPool.hpp"
CSC_BEGIN

TokenPool::TokenPool(){
    initIgnoredToken();
    initConvToken();
    initPluralRule();
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

    switch(tokens_.front() -> type){
        case TokenType::Limitor:              //如果当前token是一个定界符，那么则以多token模式填充TokenHolder
            holder.plural_ = true;
            fillHolderAsPlural(holder);
            break;
        default:                                        //默认以单token模式填充TokenHolder
            holder.plural_ = false;
            fillHolderAsNonPlural(holder);
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
    rule_.push_back({    "{", "}"   });
    rule_.push_back({    "(", ")"   });
    rule_.push_back({    "[", "]"   });
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

bool TokenPool::isPluralTokenBegin(const String &str){
    for(const auto &rule : rule_){
        if(rule.first == str) return true;
    }

    return false;
}

bool TokenPool::isPluralTokenEnd(const String &str){
    for(const auto &rule : rule_){
        if(rule.second == str) return true;
    }

    return false;
}

void TokenPool::fillHolderAsPlural(TokenHolder &holder){
    if(!isPluralTokenBegin(tokens_.front() -> str)) throw LexExcept("Invalid limitor token: " + tokens_.front() -> str);
    tokens_.pop_front();  //跳过作为起始的limitor

    /* 持续添加后续token，直到遇到作为结尾的limitor */
    while(!tokens_.empty()){
        auto tp = tokens_.front();
        if(tp -> type == TokenType::Limitor && isPluralTokenEnd(tp -> str)){
            tokens_.pop_front();      //清理掉结尾的limitor
            break;
        }

        holder.addToken(tp);
        tokens_.pop_front();        //每添加一个token，删除list中对应的token
    }
}

void TokenPool::fillHolderAsNonPlural(TokenHolder &holder){
    holder.addToken(tokens_.front());
    tokens_.pop_front();
}

CSC_END