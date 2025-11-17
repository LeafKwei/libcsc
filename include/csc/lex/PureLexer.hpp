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

/**
 * PureLexer用于将字符串的一部分分解为单个或一组Token。在其内部实现中，通过ReaderList保存所有用于读取Token的TokenReader对象，然后通过使用std::map将
 * 特定字符与这些TokenReader建立关系，在读取时，通过提取字符串的当前字符查找对应的TokenReader进行读取。PureLexer使用了Level和Mode两种机制，Level机制
 * 使得PureLexer可以将TokenReader和一些辅助信息保存到不同的级别中，在读取过程中通过调整级别就可决定是否屏蔽某些TokenReader；Mode机制决定了PureLexer
 * 是一次读取一个Token还是多个Token，用于解决数组的读取问题。
 */
class PureLexer{
public:
    constexpr static int MaxLevel = 2;   //修改此处以增加新Level
    using Flag                   = LexerFlag;
    using GuideMap         = std::map<Char, LexerGuide>;
    using ReaderList         = std::vector<TokenReaderPtr>;
    using IDMapArray      = std::array<std::map<Char, std::vector<int>>, MaxLevel>;
    using TypeListArray    = std::array<std::vector<TokenType>, MaxLevel>;
    using IdentMapArray = std::array<std::map<String, TokenType>, MaxLevel>;
    using InitTokenTypes  = std::initializer_list<TokenType>;

public:
    PureLexer();

private:
    friend                       LexerAgent;
    int                            level_;
    LexerGuide              guide_;
    ReaderList                readers_;
    IDMapArray             idMaps_;
    TypeListArray           dropedTypes_;
    IdentMapArray        identMaps_;
    GuideMap               guideMap_;

    bool guide(CharMngr &mngr);                                         /* 提取CharMngr的首个字符，并根据该字符决定PureLexer的运行级别和模式 */
    void selectLevel(LexerLevel level);                                     /* 切换到指定的Lexer环境当中 */
    int    addReader(TokenReaderPtr reader);                        /* 将指定reader添加到readerList中，并返回该reader的ID */
    void addIDMapping(const String &chs, int id);                /* 按照特定规则将字符分别添加到IDMapper中作为key，并创建对应的IDList对象，然后将id添加到列表中 */
    void addDropedType(InitTokenTypes types);                  /* 添加指定的TokenType到dropedTypeList_，当读取到该列表中所包含的类型的Token时，丢弃该Token */
    void addIdentMapping(const String &identifier, TokenType type);  /* 添加identifier类型转换，如果Identier类型的Token内容与参数identier一致，则将其类型转换为type */
    void addGuideMapping(Char ch, LexerGuide guide);     /* 添加LexerGuider映射 */
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