#include "csc/types.hpp"
#include "csc/lex/readers.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

PureLexer::PureLexer(){}

LxErrno PureLexer::readToken(CharMngr &mngr, TokenPool &pool){
    if(!mngr.valid()) return LxErrno::Done;

    auto id = findReader(mngr);
    if(id == -1){
        return LxErrno::Bad;
    }

    auto &reader = readers_.at(id);
    reader.initor(reader.local);
    const auto &pair = reader.read(mngr, reader.local);
    reader.fintor(reader.local);

    if(pair.first != RdErrno::OK){
        return LxErrno::Bad;
    }

    /* todo 保存token到pool */
    
    return LxErrno::OK;
}

void PureLexer::installReaders(){

}

int PureLexer::findReader(CharMngr &mngr){
    auto pos = chmapping_.find(mngr.getch());
    if(pos == chmapping_.end()) return -1;

    /* 遍历vector中的每个id，获取id对应的reader，然后调用其readable函数判断其是否可读取下一个token */
    const auto & vec = pos -> second;
    for(auto id : vec){
        auto &reader = readers_.at(id);
        if(reader.readable(mngr, reader.local)){
            return id;
        }
    }

    return -1;
}

void PureLexer::addCharMapping(Char ch, int id){
    auto pos = chmapping_.find(ch);
    if(pos == chmapping_.end()){
        chmapping_.emplace(ch);
    }

    chmapping_.at(ch).push_back(id);
}

void PureLexer::addCharMapping(const String &chs, int id){
    /* 支持以a-z的格式添加字符 */
    if(chs.size() == 3 && chs.at(1) == '-'){
        auto ch1 = chs.at(0);
        auto ch2 = chs.at(2);

        for(; ch1 <= ch2; ch1++){
            addCharMapping(ch1, id);
        }

        return;
    }
    
    /* 其他情况下遍历所有字符并依次添加 */
    for(auto ch : chs){
        addCharMapping(ch, id);
    }
}

int PureLexer::addReader(ReaderReadable readable, ReaderRead read){
    addReader(default_initor, readable, read, default_fintor, 0);
}

int PureLexer::addReader(ReaderReadable readable, ReaderRead read, ReaderFlag flag){
    addReader(default_initor, readable, read, default_fintor, flag);
}

int PureLexer::addReader(ReaderInitor initor, ReaderReadable readable, ReaderRead read, ReaderFintor fintor, ReaderFlag flag){
    readers_.push_back(TokenReader{
        0,
        0,
        default_initor,
        readable,
        read,
        default_fintor
    });
}

CSC_END