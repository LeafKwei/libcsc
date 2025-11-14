#include "csc/types.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

void PureLexer::selectEnv(LexerEnvid id){
    envid_ = static_cast<int>(id);
}

int PureLexer::addReader(TokenReaderPtr reader){
    if(reader == nullptr) throw LexExcept("Can't add reader pointed to nullptr.");
    readers_.push_back(reader);
    return readers_.size() - 1;
}

void PureLexer::mappingReader(const String &chs, int id){
    for(const auto &ch : chs){
        makeIDListFor(ch);
        appendID(ch, id);
    }
}

void PureLexer::mappingReader(const CharRange &range, int id){
    for(auto ch = range.lch; ch <= range.rch; ch++){
        makeIDListFor(ch);
        appendID(ch, id);
    }
}

void PureLexer::addDropedType(PureLexer::InitTokenTypes types){
    for(auto type : types){
        dropedTypeArray_[envid_].push_back(type);
    }
}

void PureLexer::makeIDListFor(Char ch){
    auto pos = mapperArray_[envid_].find(ch);
    if(pos != mapperArray_[envid_].end()) return;
    mapperArray_[envid_].emplace(ch);
}

void PureLexer::appendID(Char ch, int id){
    auto pos = mapperArray_[envid_].find(ch);
    pos -> second.push_back(id);
}

int PureLexer::findReaderID(CharMngr &mngr){
    /* 根据首个字符寻找是否存在对应的ID列表 */
    auto pos = mapperArray_[envid_].find(mngr.getch());
    if(pos == mapperArray_[envid_].end()) return -1;

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