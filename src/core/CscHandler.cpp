#include "csc/core/CscHandler.hpp"
#include "csc/core/CscStrSeeker.hpp"
CSC_BEGIN

CscHandler::CscHandler(crString script){
    m_driver.drive(script, m_context);
}

bool CscHandler::accessible(crString path, bool v){
    PathHelper helper(path);
    if(!helper.valid()) return false;
    if(helper.isRoot()) return true; //对于根路径'/'的特别处理

    Detector detector = m_context.detector(helper.isAbsolute());
    for(Size_t i = 0; i < helper.size(); i++){
        if(v && i == helper.size() - 1){                             //当检查variable路径时，将最后一个item作为variable名称处理
            if(!detector.detectVariable(helper.item(i))) return false;
        }

        if(!detector.tryEnter(helper.item(i))) return false;    //其他情况下都做scope名称处理
    }

    return true;
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