#ifndef CSC_PURELEXER_HPP
#define CSC_PURELEXER_HPP

#include <map>
#include <vector>
#include "csc/alias.hpp"
#include "csc/lex/types.hpp"
#include "csc/lex/CharMngr.hpp"
#include "csc/lex/TokenReader.hpp"
#include "csc/lex/TokenHolder.hpp"
CSC_BEGIN

class PureLexer{
public:
    using ReaderList            = std::vector<TokenReaderPtr>;
    using ReaderIDList        = std::vector<int>;
    using ReaderIDMapper = std::map<Char, ReaderIDList>;
    using ReaderIDListPos  = ReaderIDMapper::iterator;
    using InitTokenTypes     = std::initializer_list<TokenType>;
    using DropedTypeList   = std::vector<TokenType>;

public:
    LexerState nextFrom(TokenHolder &holder, CharMngr &mngr);   /* 基于mngr进行下一次的token读取，返回true代表读取成功，返回false代表无更多内容可读取 */

private:
    friend                   PureLexerAgent;
    ReaderList            readerList_;
    ReaderIDMapper readerIDMapper_;
    DropedTypeList   dropedTypeList_;

    int    addReader(TokenReaderPtr reader);                        /* 将指定reader添加到readerList中，并返回该reader的ID */
    void mappingReader(const String &chs, int id);              /* 将chs中的每个字符分别添加到readerIDMapper中作为key，并创建对应的ReaderIDList对象，然后将id添加到列表中 */
    void mappingReader(const CharRange &range, int id); /* 将range中lch和rch之间(包括lch和rch)的所有字符添加到eaderIDMapper中作为key，后续操作同上 */
    void addDropedType(InitTokenTypes types);                  /* 添加指定的TokenType到dropedTypeList_，当读取到该列表中所包含的类型的Token时，丢弃该Token */
    void makeIDListFor(Char ch);
    void appendID(Char ch, int id);
    int findReaderID(CharMngr &mngr);
};

CSC_END
#endif