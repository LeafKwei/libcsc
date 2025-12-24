#include "csc/core/CscHandler.hpp"
#include "csc/core/CscStrSeeker.hpp"
CSC_BEGIN

CscHandler::CscHandler(const String &script){
    driver_.drive(script, context_);
}

int CscHandler::handle(const String &script){
    return driver_.drive(script, context_);
}

bool CscHandler::accessible(const String &path, bool v){
    PathHelper helper(path);
    if(!helper.valid()) return false;
    if(helper.rootonly()) return !(v);                                      //对于根路径'/'的特别处理，当参数v为true时，由于根目录不是变量，所以要返回false

    auto end = (helper.size() > 0) ? helper.size() - 1 : 0;      //仅遍历路径最后一个item之前的item
    auto querier = context_.querier(helper.absolute());

    /* 对于路径的前面部分，都视作scope名称检查 */
    for(Size_t i = 0; i < end; i++){
        if(!querier.tryEnter(helper.element(i))) return false;
    }

    /* 最后一部分则根据参数v决定是作为scope名称还是variable名称检查 */
    return (v) ? querier.hasVariable(helper.basename()) : querier.hasScope(helper.basename());
}

String CscHandler::absolutePath(){
    return String("/") + context_.relation("/");
}

CscHandler& CscHandler::enter(const String &path){
    PathHelper helper(path);

    if(!helper.valid()) throw CscExcept("Invalid path: " + path);
    if(helper.absolute()){  //如果是根路径'/'，由于helper.size()为0，所以下方的循环不会执行
        context_.restart();   //因此通过这条语句既可以处理根路径，也可以处理绝对路径
    }

    for(Size_t idx = 0; idx < helper.size(); idx++){
        context_.enterScope(helper.element(idx));
    }

    return *this;
}

CscHandler& CscHandler::iterate(ContextSeeker &seeker){
    context_.iterate(seeker);
    return *this;
}

String CscHandler::toString(){
    CscStrSeeker seeker;
    context_.iterate(seeker);
    return seeker.toString();
}

CscEditor CscHandler::editor(){
    return CscEditor(context_);
}
CSC_END