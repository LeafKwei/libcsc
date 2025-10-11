#include <iostream>
#include <sstream>
#include "csc/lex/PureLexer.hpp"
#include "csc/lex/readers.hpp"
#include "csc/lex/functions.hpp"
CSC_BEGIN

//============== CommonReader =============
/** 
 * CommonReader将token的读取抽象为了字符判断、字符读取、获取选项、获取类型等部分，对于一些结构简单的token，仅需实现以上函数
 * 即可完成读取，而无需重写整个read函数
 */
Token CommonReader::read(CharMngr &mngr){
    Token token{};

    while(mngr.valid()){
        if(!canRead(mngr.getch())) break;
        token.str.push_back(mngr.forward());
    }

    token.type = type();
    return token;
}

bool CommonReader::readable(CharMngr &mngr){
    return false;
}

TokenType CommonReader::type(){
    return TokenType::Unknown;
}

bool CommonReader::canRead(Char ch){
    return false;
}

//============== BlankReader =============
bool BlankReader::readable(CharMngr &mngr){
    return mngr.valid() && isBlank(mngr.getch());
}

TokenType BlankReader::type(){
    return TokenType::Blank;
}

bool BlankReader::canRead(Char ch){
    return isBlank(ch);
}

//============== DescriptionReader =============
bool DescriptionReader::readable(CharMngr &mngr){
    return mngr.valid() && (mngr.getch() == ';');
}

TokenType DescriptionReader::type(){
    return TokenType::Description;
}

bool DescriptionReader::canRead(Char ch){
    if(!isNewLine(ch)) return true;
    return false;
}

//============== IdentifierReader =============
bool IdentifierReader::readable(CharMngr &mngr){
    return mngr.valid() && (isAlpha(mngr.getch()) || mngr.getch() == '_');
}

TokenType IdentifierReader::type(){
    return TokenType::Identifier;
}

bool IdentifierReader::canRead(Char ch){
    return isIdentifier(ch);
}

//============== OperatorReader =============
bool OperatorReader::readable(CharMngr &mngr){
    return mngr.valid() && isOperator(mngr.getch());
}

TokenType OperatorReader::type(){
    return TokenType::Operator;
}

bool OperatorReader::canRead(Char ch){
    return isOperator(ch);
}

//============== NumberReader =============
bool NumberReader::readable(CharMngr &mngr){
    if(mngr.valid() && isNumber(mngr.getch())) return true;
    
    /* 检查token是否以+-符号开头 */
    if(mngr.valid() && (mngr.getch() == '+' || mngr.getch() == '-')) return true;

    /* 检查token是否含有0x前缀 */
    if(mngr.index() + 1 >= mngr.length()) return false;
    if(mngr.at(mngr.index()) == '0' && mngr.at(mngr.index() + 1) == 'x') return true;

    return false;
}

Token NumberReader::read(CharMngr &mngr){
    Token token{TokenType::Number};
    readPrefix(token, mngr);

    m_num = 0;
    if(m_type == 1) readHex(token, mngr);
    if(m_type == 0) readNumber(token, mngr);

    /* 如果在前缀之后没有读取到任何一个数字，则说明token有误 */
    if(m_num == 0){
        token.type = TokenType::Unknown;
    }

    /* 如果数字字符之后不是空白字符或者“,”结尾，则说明token有误(例如123abc) */
    if(mngr.valid() && (!isBlank(mngr.getch()) && !(isSeparator(mngr.getch())))){
       token.type = TokenType::Unknown;
    }

    return token;
}

TokenType NumberReader::type(){
    return TokenType::Number;
}

void NumberReader::readPrefix(Token &token, CharMngr &mngr){
    /* 对于16进制的前缀0x的检查必须放在前面，否则字符0将被作为数字token读取 */
    if(mngr.at(mngr.index()) == '0' && mngr.at(mngr.index() + 1) == 'x'){
        m_type = 1;
        token.str.push_back(mngr.forward());
        token.str.push_back(mngr.forward());
        return;
    }

    if(mngr.valid() && isNumber(mngr.getch())){
        m_type = 0;
        return;
    }
    
    if(mngr.valid() && (mngr.getch() == '+' || mngr.getch() == '-')){
        m_type = 0;
        token.str.push_back(mngr.forward());
        return;
    }
}

void NumberReader::readHex(Token &token, CharMngr &mngr){
    token.tag = TokenTag::Hex;
    
    while(mngr.valid()){
        if(!isHexNumber(mngr.getch())) break;
        token.str.push_back(mngr.forward());
        m_num++;
    }
}

void NumberReader::readNumber(Token &token, CharMngr &mngr){
    bool dot = true;

    while(mngr.valid()){
        auto ch = mngr.getch();
        if(!isNumber(ch) && !(dot && ch == '.')) break;  //如果一个字符既不是数字字符也不是点，则停止读取
        if(ch == '.'){                                                            //读取到dot时，表示该token是一个浮点数
            token.tag = TokenTag::Float;
            dot = false;
        }

        token.str.push_back(mngr.forward());
        m_num++;
    }
}

//============== StringReader =============
bool StringReader::readable(CharMngr &mngr){
    return mngr.valid() && mngr.getch() == '"';
}

Token StringReader::read(CharMngr &mngr){
    Token token{TokenType::String};
    readString(token, mngr);
    return token;
}

TokenType StringReader::type(){
    return TokenType::String;
}

void StringReader::readString(Token &token, CharMngr &mngr){
    mngr.forward();  //跳过首个引号

    bool escape = false;
    while(mngr.valid()){
        Char ch = mngr.forward();

        if(escape){
            escape = false;
            token.str.push_back(escapeTo(ch));
            continue;
        }

        if(isEscape(ch)){
            escape = true;
            continue;
        }

        if(ch == '"'){
            return;
        }

        token.str.push_back(ch);
    }

    if(!(mngr.valid())){ //当到达string末尾时，如果还没找到引号，则说明字符串边界有误
        token.type = TokenType::Unknown;
    }
}

//============== ArrayReader =============
bool ArrayReader::readable(CharMngr &mngr){
    return mngr.valid() && mngr.getch() == '{';
}

TokenType ArrayReader::type(){
    return TokenType::Array;
}

Token ArrayReader::read(CharMngr &mngr){
    Token token{TokenType::Array};

    mngr.forward();   //跳过首个{

    /* 读取{}中的所有内容 */
    while(mngr.valid()){
        if(mngr.getch() == '}') break;
        token.str.push_back(mngr.forward());
    }

    if(!mngr.valid()){  //类似于字符串，如果数组没有以}结尾，则视为错误
        token.type = TokenType::Unknown;
        return token;
    }

    mngr.forward(); //跳过末尾的}
    return token;
}

CSC_END