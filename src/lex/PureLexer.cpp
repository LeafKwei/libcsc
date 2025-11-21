#include "csc/types.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

PureLexer::PureLexer(){}

PureLexer::Flag PureLexer::nextFrom(CharMngr &mngr, TokenHolder &holder){
    initialize();
}

int PureLexer::addReader(TokenReaderPtr reader){
    if(reader == nullptr) throw LexExcept("Can't add reader pointed to nullptr.");
    readers_.push_back(reader);
    return readers_.size() - 1;
}

void initialize(){

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
        dropedTypes_.push_back(type);
    }
}

 void PureLexer::addIdentifierMapping(const String &identier, TokenType type){
    identifierMap_.insert({identier, type});
 }

 void PureLexer::makeIDListFor(Char ch){
    auto pos = idMap_.find(ch);
    if(pos != idMap_.end()) return;
    idMap_.emplace(ch);
}

void PureLexer::appendID(Char ch, int id){
    auto pos = idMap_.find(ch);
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
    /* 根据首个字符寻找是否存在对应的迭代器 */
    auto pos = idMap_.find(mngr.getch());
    if(pos == idMap_.end()) return -1;

    /* 获取ID列表并遍历，找到匹配的TokenReader并返回ID */
    const auto &idList = pos -> second;
    for(auto id : idList){
        if(readers_.at(id) -> readable(mngr)){
            return id;
        }
    }

    return -1;
}

bool PureLexer::isDropedToken(TokenType type){
    for(auto i = 0UL; i < dropedTypes_.size(); i++){
        if(dropedTypes_.at(i) == type) return true;
    }

    return false;
}

void PureLexer::setIdentifierType(Token &token){
    auto pos = identifierMap_.find(token.str);
    if(pos == identifierMap_.end()){
        return;
    }

    token.type = pos -> second;
}

CSC_END