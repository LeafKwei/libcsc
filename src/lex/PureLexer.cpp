#include "csc/types.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

PureLexer::PureLexer() : envid_(0){}

void PureLexer::selectEnv(LexerEnvid id){
    envid_ = static_cast<int>(id);
}

int PureLexer::addReader(TokenReaderPtr reader){
    if(reader == nullptr) throw LexExcept("Can't add reader pointed to nullptr.");
    readers_.push_back(reader);
    return readers_.size() - 1;
}

void PureLexer::mappingID(const String &chs, int id){
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
        dropedTypeArray_[envid_].push_back(type);
    }
}

 void PureLexer::addTypeMapper(const String &identier, TokenType type){
    typeMapperArray_[envid_].insert({identier, type});
 }

void PureLexer::makeIDListFor(Char ch){
    auto pos = idMapperArray_[envid_].find(ch);
    if(pos != idMapperArray_[envid_].end()) return;
    idMapperArray_[envid_].emplace(ch);
}

void PureLexer::appendID(Char ch, int id){
    auto pos = idMapperArray_[envid_].find(ch);
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
    /* 根据首个字符寻找是否存在对应的ID列表 */
    auto pos = idMapperArray_[envid_].find(mngr.getch());
    if(pos == idMapperArray_[envid_].end()) return -1;

    /* 根据ID列表中的ID遍历对应的TokenReader，如果其readable函数返回为true，则返回该Reader的ID */
    const auto &idList = pos -> second;
    for(auto id : idList){
        if(readers_.at(id) -> readable(mngr)){
            return id;
        }
    }

    return -1;
}

CSC_END