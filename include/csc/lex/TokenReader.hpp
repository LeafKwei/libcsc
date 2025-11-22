#ifndef CSC_TOKENREADER_HPP
#define CSC_TOKENREADER_HPP

#include <map>
#include <functional>
#include "csc/lex/types.hpp"
#include "csc/lex/CharMngr.hpp"
CSC_BEGIN

enum class RdErrno {
    OK, Broken
};

////////////////////////////////////////////////////////////////////////////////////////

using TokenPair           = std::pair<RdErrno, Token>;
using ReaderInitor       = std::function<void(Any &local)>;
using ReaderReadable = std::function<bool(CharMngr &mngr, Any &local)>;
using ReaderRead        = std::function<TokenPair(CharMngr &mngr, Any &local)>;
using ReaderFintor      =  std::function<void(Any &local)>;
using ReaderFlag         = unsigned long long; 

////////////////////////////////////////////////////////////////////////////////////////

struct TokenReader{
    Any                     local;      //local字段用于提供给Reader的各个函数保存一些依赖信息
    ReaderFlag          flag;      //flag用作保留字段，暂无作用
    ReaderInitor        initor;   //初始化local字段
    ReaderReadable readable; //检查当前Reader是否可以读取下一个Token
    ReaderRead        read;      //读取下一个Token
    ReaderFintor       fintor;   //释放local字段
};

////////////////////////////////////////////////////////////////////////////////////////

constexpr ReaderFlag RDFLAG_NONE = 0;


CSC_END
#endif