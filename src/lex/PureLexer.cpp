#include "csc/types.hpp"
#include "csc/lex/readers.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

PureLexer::PureLexer(){
    installReaders();
}

LxErrno PureLexer::readToken(CharMngr &mngr, TokenPool &pool){
    if(!mngr.valid()) return LxErrno::Done;

    auto id = findReader(mngr);
    if(id == -1){
        return LxErrno::Bad;
    }

    auto &reader = readers_.at(id);
    const auto &pair = reader.read(mngr, reader.local);
    reader.fintor(reader.local);

    if(pair.first != RdErrno::OK){
        return LxErrno::Bad;
    }

    pool.addToken(pair.second);    
    return LxErrno::OK;
}

void PureLexer::installReaders(){
    int id = 0;

    ////////////////////////////////////////////////////////////////////////////////////////Blank
    id = addReader(blank_readable, blank_read);
    addCharMapping(" \t\n", id);   //注意有个空格

    ////////////////////////////////////////////////////////////////////////////////////////Description
    id = addReader(description_readable, description_read);
    addCharMapping(";", id);

    ////////////////////////////////////////////////////////////////////////////////////////Limitor
    id = addReader(limitor_readable, limitor_read);
    addCharMapping("{}()[]", id);

    ////////////////////////////////////////////////////////////////////////////////////////Separator
    id = addReader(separator_readable, separator_read);
    addCharMapping(",", id);

    ////////////////////////////////////////////////////////////////////////////////////////Identifier
    id = addReader(identifier_readable, identifier_read);
    addCharMapping("A-Z", id);
    addCharMapping("a-z", id);
    addCharMapping("_", id);

    ////////////////////////////////////////////////////////////////////////////////////////Operator
    id = addReader(operator_readable, operator_read);
    addCharMapping(":=", id);

    ////////////////////////////////////////////////////////////////////////////////////////Number
    id = addReader(number_initor, number_readable, number_read);
    addCharMapping("+-", id);
    addCharMapping("0-9", id);

    ////////////////////////////////////////////////////////////////////////////////////////String
    id = addReader(string_readable, string_read);
    addCharMapping("\"", id);
}

int PureLexer::findReader(CharMngr &mngr){
    /* 在chmapping中寻找是否有与指定字符对应的vector */
    auto pos = chmapping_.find(mngr.getch());
    if(pos == chmapping_.end()) return -1;

    /* 遍历vector中的每个id，获取id对应的reader，然后调用其readable函数判断其是否可读取下一个token */
    const auto & vec = pos -> second;
    for(auto id : vec){
        auto &reader = readers_.at(id);
        reader.initor(reader.local);   //在readable调用前调用initor初始化local字段
        if(reader.readable(mngr, reader.local)){
            return id;
        }
        reader.fintor(reader.local);   //如果当前reader不是我们需要的reader，则立刻调用fintor释放local字段
    }

    return -1;
}

void PureLexer::addCharMapping(Char ch, int id){
    auto pos = chmapping_.find(ch);
    if(pos == chmapping_.end()){
        chmapping_.insert({ch, IntegerList{}});
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
    return addReader(default_initor, readable, read, default_fintor, 0);
}

int PureLexer::addReader(ReaderReadable readable, ReaderRead read, ReaderFlag flag){
    return addReader(default_initor, readable, read, default_fintor, flag);
}

int PureLexer::addReader(ReaderInitor initor, ReaderReadable readable, ReaderRead read){
    return addReader(initor, readable, read, default_fintor, 0);
}

int PureLexer::addReader(ReaderInitor initor, ReaderReadable readable, ReaderRead read, ReaderFlag flag){
    return addReader(initor, readable, read, default_fintor, flag);
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

    return readers_.size() - 1;
}

CSC_END