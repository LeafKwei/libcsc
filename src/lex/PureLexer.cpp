#include "csc/types.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

LexerState PureLexer::nextFrom(TokenHolder &holder, CharMngr &mngr){
    if(!mngr.valid()) return LexerState::Finish;

    auto id = findReaderID(mngr);
    if(id == -1) return LexerState::Unexcepted;

    
}

int PureLexer::addReader(TokenReaderPtr reader){
    if(reader == nullptr) throw LexExcept("Can't add reader pointed to nullptr.");
    readerList_.push_back(reader);
    return readerList_.size() - 1;
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
        dropedTypeList_.push_back(type);
    }
}

void PureLexer::makeIDListFor(Char ch){
    auto pos = readerIDMapper_.find(ch);
    if(pos != readerIDMapper_.end()) return;
    readerIDMapper_.emplace(ch);
}

void PureLexer::appendID(Char ch, int id){
    auto pos = readerIDMapper_.find(ch);
    pos -> second.push_back(id);
}

int PureLexer::findReaderID(CharMngr &mngr){
    /* 根据首个字符寻找是否存在对应的ID列表 */
    auto pos = readerIDMapper_.find(mngr.getch());
    if(pos == readerIDMapper_.end()) return -1;

    /* 根据ID列表中的ID遍历对应的TokenReader，如果其readable函数返回为true，则返回该Reader的ID */
    const auto &idList = pos -> second;
    for(auto id : idList){
        if(readerList_.at(id) -> readable(mngr)){
            return id;
        }
    }

    return -1;
}

CSC_END