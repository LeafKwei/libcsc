#include "csc/core/CscHandler.hpp"
#include "csc/core/CscStrSeeker.hpp"
CSC_BEGIN

CscHandler::CscHandler(crString script){
    m_driver.drive(script, m_context);
}

bool CscHandler::accessible(crString path, bool v){
    PathHelper helper(path);
    if(!helper.valid()) return false;
    if(helper.isRoot()) return !(v); //对于根路径'/'的特别处理，当参数v为true时，由于根目录不是变量，所以要返回false

    auto end = (helper.size() > 0) ? helper.size() - 1 : 0;                   //仅遍历路径最后一个item之前的item
    Detector detector = m_context.detector(helper.isAbsolute());

    /* 对于路径的前面部分，都视作scope名称检查 */
    for(Size_t i = 0; i < end; i++){
        if(!detector.tryEnter(helper.item(i))) return false;
    }

    /* 最后一部分则根据参数v决定是作为scope名称还是variable名称检查 */
    return (v) ? detector.detectVariable(helper.lastItem()) : detector.detectScope(helper.lastItem());
}

String CscHandler::absolutePath(){
    return String("/") + m_context.relation("/");
}

CscHandler& CscHandler::enter(crString path){
    PathHelper helper(path);
    if(!helper.valid()) throw CscExcept("Invalid path: " + path);
    if(helper.isAbsolute()){  //如果是根路径'/'，由于helper.size()为0，所以下方的循环不会执行
        m_context.restart();  //因此通过这条语句既可以处理根路径，也可以处理绝对路径
    }

    for(Size_t i = 0; i < helper.size(); i++){
        m_context.enterScope(helper.item(i));
    }

    return *this;
}

CscHandler& CscHandler::iterate(ContextSeeker &seeker){
    m_context.iterate(seeker);
    return *this;
}

String CscHandler::toString(){
    CscStrSeeker seeker;
    m_context.iterate(seeker);
    return seeker.toString();
}

CscEditor CscHandler::editor(){
    return CscEditor(m_context);
}
CSC_END