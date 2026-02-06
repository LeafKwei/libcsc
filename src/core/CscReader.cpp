#include "csc/core/CscReader.hpp"
#include "csc/core/CscString.hpp"
CSC_BEGIN

CscReader::CscReader(Context &context) : context_(context){
    
}

bool CscReader::accessible(const String &path, bool v) const{
    PathHelper helper(path);
    if(!helper.valid()) return false;
    if(helper.rootonly()) return !(v);                                      //对于根路径'/'的特别处理，当参数v为true时，由于根目录不是变量，所以要返回false

    auto end = (helper.size() > 0) ? helper.size() - 1 : 0;      //仅遍历路径最后一个item之前的item
    auto looker = context_.routelooker(helper.absolute());

    /* 对于路径的前面部分，都视作scope名称检查 */
    for(Size_t i = 0; i < end; i++){
        looker.looksco(helper.element(i));
    }

    /* 最后一部分则根据参数v决定是作为scope名称还是variable名称检查 */
    return (v) 
        ? looker.lookvar(helper.basename()).done() 
        : looker.looksco(helper.basename()).done();
}

void CscReader::enter(const String &path) const{
    PathHelper helper(path);

    if(!helper.valid()) throw CscExcept("Invalid path: " + path);
    if(helper.absolute()){  //如果是根路径'/'，由于helper.size()为0，所以下方的循环不会执行
        context_.restart();   //因此通过这条语句既可以处理根路径，也可以处理绝对路径
    }

    for(Size_t idx = 0; idx < helper.size(); idx++){
        context_.enterScope(helper.element(idx));
    }
}

ScoQuerier CscReader::scoquerier() const{
    return context_.scoquerier();
}

String CscReader::toString() const{
    CscString cscstr(context_.scoquerier(), context_.isRootScope());
    return cscstr.localstr();
}

void CscReader::enterBeforeGet(PathHelper &helper) const{
    if(!helper.valid()){
        throw CscExcept("Invalid path: " + helper.compose(helper.size()));
    }

    /* 如果path仅是一个根路径，则视为错误 */
    if(helper.rootonly()){
        throw CscExcept("No variable name provided.");
    }

    /* 如果path存在dirname部分，进入对应路径下 */
    if(helper.complex()){
        enter(helper.dirname());
    }
}

CSC_END