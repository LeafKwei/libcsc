#ifndef CSC_PURELEXER_HPP
#define CSC_PURELEXER_HPP

#include <map>
#include <vector>
#include <array>
#include "csc/alias.hpp"
#include "csc/lex/types.hpp"
#include "csc/lex/CharMngr.hpp"
#include "csc/lex/TokenReader.hpp"
CSC_BEGIN

class PureLexer{
public:
    using ReaderList            = std::vector<TokenReaderPtr>;
    using IDList                    = std::vector<int>;
    using IDMapper             = std::map<Char, IDList>;
    using IDListPos              = IDMapper::iterator;
    using TypeMapper         = std::map<String, TokenType>;
    using InitTokenTypes     = std::initializer_list<TokenType>;
    using DropedTypeList    = std::vector<TokenType>;
    using IDMapperArray    = std::array<IDMapper, 2>;    //如果需要增加新的环境，可以调整此处的数量
    using TypeListArray        = std::array<DropedTypeList, 2>;
    using TypeMapperArray = std::array<TypeMapper, 2>;

public:
    PureLexer();

private:
    friend                    LexerAgent;
    int                         envid_;
    ReaderList             readers_;
    IDMapperArray     idMapperArray_;
    TypeListArray        dropedTypeArray_;
    TypeMapperArray typeMapperArray_;

    void selectEnv(LexerEnvid env);                                        /* 切换到指定的Lexer环境当中 */
    int    addReader(TokenReaderPtr reader);                        /* 将指定reader添加到readerList中，并返回该reader的ID */
    void mappingID(const String &chs, int id);                     /* 按照特定规则将字符分别添加到IDMapper中作为key，并创建对应的IDList对象，然后将id添加到列表中 */
    void addDropedType(InitTokenTypes types);                  /* 添加指定的TokenType到dropedTypeList_，当读取到该列表中所包含的类型的Token时，丢弃该Token */
    void addTypeMapper(const String &identier, TokenType type); /* 添加identifier类型转换，如果Identier类型的Token内容与参数identier一致，则将其类型转换为type */
    void makeIDListFor(Char ch);
    void appendID(Char ch, int id);
    void enumedMapping(const String &chs, int id);            /* 添加chs中的每个字符 */
    void rangedMapping(Char lch, Char rch, int id);              /* 添加lch和rch及其之间的所有字符 */
    int   findReaderID(CharMngr &mngr);

};

CSC_END
#endif