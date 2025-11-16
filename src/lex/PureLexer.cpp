#include "csc/types.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

PureLexer::PureLexer() : level_(0){}

void PureLexer::selectLevel(LexerLevel id){
    level_ = static_cast<int>(id);
}

int PureLexer::addReader(TokenReaderPtr reader){
    if(reader == nullptr) throw LexExcept("Can't add reader pointed to nullptr.");
    readers_.push_back(reader);
    return readers_.size() - 1;
}

void PureLexer::addIDMapping(const String &chs, int id){
    /* 如果chs中的内容仅有三个字符，并且满足a-z这类格式，则执行区间式映射 */
    if(chs.size() == 3 && chs.at(1) == '-'){
        rangedMapping(chs.at(0), chs.at(2), id);
        return;
    }

    /* 否则执行枚举式映射 */
    enumedMapping(chs, id);
}

void PureLexer::addDropedType(PureLexer::InitTokenTypes types){
    for(auto type : types){
        dropedTypes_[level_].push_back(type);
    }
}

 void PureLexer::addIdentMapping(const String &identier, TokenType type){
    identMappings_[level_].insert({identier, type});
 }

void PureLexer::makeIDListFor(Char ch){
    auto pos = idMappings_[level_].find(ch);
    if(pos != idMappings_[level_].end()) return;
    idMappings_[level_].emplace(ch);
}

void PureLexer::appendID(Char ch, int id){
    auto pos = idMappings_[level_].find(ch);
    pos -> second.push_back(id);
}

void PureLexer::enumedMapping(const String &chs, int id){
    for(const auto &ch : chs){
        makeIDListFor(ch);
        appendID(ch, id);
    }
}

void PureLexer::rangedMapping(Char lch, Char rch, int id){
    for(auto ch = lch; ch <= rch; ch++){
        makeIDListFor(ch);
        appendID(ch, id);
    }
}

int PureLexer::findReaderID(CharMngr &mngr){
    for(Size_t i = level_; i < idMappings_.size(); i++){
        auto id = findReaderIDOnLevel(mngr, i);
        if(id != -1) return id;
    }

    return -1;
}

int PureLexer::findReaderIDOnLevel(CharMngr &mngr, int level){
    /* 根据首个字符寻找是否存在对应的ID列表 */
    auto pos = idMappings_[level].find(mngr.getch());
    if(pos == idMappings_[level].end()) return -1;

    /* 根据ID列表中的ID遍历对应的TokenReader，如果其readable函数返回为true，则返回该Reader的ID */
    const auto &idList = pos -> second;
    for(auto id : idList){
        if(readers_.at(id) -> readable(mngr)){
            return id;
        }
    }

    return -1;
}

bool PureLexer::isDropedToken(TokenType type){
    for(Size_t i = level_; i < dropedTypes_.size(); i++){
        auto b = isDropedTokenOnLevel(type, i);
        if(b) return b;
    }

    return false;
}

bool PureLexer::isDropedTokenOnLevel(TokenType type, int level){
    for(auto i = 0UL; i < dropedTypes_[level].size(); i++){
        if(dropedTypes_[level].at(i) == type) return true;
    }
    return false;
}

void PureLexer::setIdentifierType(Token &token){
    if(token.type != TokenType::Identifer) return;

    for(auto i = 0UL; i < identMappings_.size(); i++){
        if(setIdentifierTypeOnLevel(token, i)) return;
    }
}

bool PureLexer::setIdentifierTypeOnLevel(Token &token, int level){
    /* 没有找到对应的TokenType时，返回false，使setIdentifierType继续迭代 */
    auto pos = identMappings_.at(level).find(token.str);
    if(pos == identMappings_.at(level).end()){
        return false;
    }

    /* 找到TokenType时返回true，不进行后续迭代  */
    token.type = pos -> second;
    return true;
}

CSC_END