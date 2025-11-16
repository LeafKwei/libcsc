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
    constexpr static int MaxLevel = 2;   //修改此处以增加新Level
    using ReaderList                = std::vector<TokenReaderPtr>;
    using IDMappingArray      = std::array<std::map<Char, std::vector<int>>, MaxLevel>;
    using TypeListArray           = std::array<std::vector<TokenType>, MaxLevel>;
    using IdentMappingArray = std::array<std::map<String, TokenType>, MaxLevel>;
    using InitTokenTypes         = std::initializer_list<TokenType>;

public:
    PureLexer();

private:
    friend                       LexerAgent;
    int                             level_;
    ReaderList                readers_;
    IDMappingArray      idMappings_;
    TypeListArray           dropedTypes_;
    IdentMappingArray identMappings_;

    void selectLevel(LexerLevel level);                                     /* 切换到指定的Lexer环境当中 */
    int    addReader(TokenReaderPtr reader);                        /* 将指定reader添加到readerList中，并返回该reader的ID */
    void addIDMapping(const String &chs, int id);                /* 按照特定规则将字符分别添加到IDMapper中作为key，并创建对应的IDList对象，然后将id添加到列表中 */
    void addDropedType(InitTokenTypes types);                  /* 添加指定的TokenType到dropedTypeList_，当读取到该列表中所包含的类型的Token时，丢弃该Token */
    void addIdentMapping(const String &identier, TokenType type); /* 添加identifier类型转换，如果Identier类型的Token内容与参数identier一致，则将其类型转换为type */
    void makeIDListFor(Char ch);
    void appendID(Char ch, int id);
    void enumedMapping(const String &chs, int id);            /* 添加chs中的每个字符 */
    void rangedMapping(Char lch, Char rch, int id);              /* 添加lch和rch及其之间的所有字符 */
    int   findReaderID(CharMngr &mngr);
    int   findReaderIDOnLevel(CharMngr &mngr, int level);
    bool isDropedToken(TokenType type);
    bool isDropedTokenOnLevel(TokenType type, int level);
    void setIdentifierType(Token &token);
    bool setIdentifierTypeOnLevel(Token &token, int level);
};

CSC_END
#endif