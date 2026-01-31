#ifndef CSC_HANDLER_HPP
#define CSC_HANDLER_HPP

#include "csc/csc.hpp"
#include "csc/context/Scope.hpp"
#include "csc/context/Context.hpp"
#include "csc/core/types.hpp"
#include "csc/core/CscReader.hpp"
#include "csc/core/CscWriter.hpp"
#include "csc/syntax/CmdDriver.hpp"
#include "csc/utility/utility.hpp"
#include "csc/utility/PathHelper.hpp"

CSC_BEGIN
/**
 * CscHandler是提供给用户使用的顶层接口，通过reader和writer接口，向用户提供对Context中保存的csc配置文件内容更简便地访问功能。 
 * 用户可根据自身需求，通过传递不同的Context实现类型作为模板参数以定制化CscHandler对于csc配置内容的存储与组织
 */
template<ScopeType TP>
class CscHandler{
public:
    CscHandler();
    CscHandler(const String &script);
    int                  handle(const String &script);                 /* 处理指定的csc文件内容，返回执行的命令数量 */
    CscReader      reader();                                                 /* 获取一个reader对象，可以读取Context中的内容  */
    CscWriter       writer();                                                  /* 获取一个writer对象，可以编辑Context中的内容 */

private:
    Context       context_;
    CmdDriver  driver_;
};

template<ScopeType TP>
inline CscHandler<TP>::CscHandler() : context_(TP){

}

template<ScopeType TP>
inline CscHandler<TP>::CscHandler(const String &script) : context_(TP){
    driver_.drive(script, context_);
}

template<ScopeType TP>
inline int CscHandler<TP>::handle(const String &script){
    return driver_.drive(script, context_);
}

template<ScopeType TP>
inline CscReader CscHandler<TP>::reader(){
    return CscReader(context_);
}

template<ScopeType TP>
inline CscWriter CscHandler<TP>::writer(){
    return CscWriter(context_);
}


CSC_END
#endif