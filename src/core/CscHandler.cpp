#include "csc/core/CscHandler.hpp"
#include "csc/core/CscStrSeeker.hpp"
CSC_BEGIN

CscHandler::CscHandler(crString script){
    m_driver.drive(script, m_context);
}

bool CscHandler::accessible(crString path, bool v){
    
}

String CscHandler::absolutePath(){
    return String("/") + m_context.relation("/");
}

CscHandler& CscHandler::enter(crString path){
   
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