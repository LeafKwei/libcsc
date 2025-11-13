#include "csc/types.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

LexerFlag PureLexer::nextFrom(TokenHolder &holder, CharMngr &mngr){
    
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

CSC_END