#include "csc/core/CscHandler.hpp"
#include "csc/core/CscStrSeeker.hpp"
#include "csc/core/functions.hpp"
CSC_BEGIN

CscHandler::CscHandler(ConstStr script){
    m_driver.drive(script, m_context);
}

CscHandler& CscHandler::enter(ConstStr path){

}

CscHandler& CscHandler::iterate(ContextSeeker &seeker){
    m_context.iterate(seeker);
    return *this;
}

CscStr CscHandler::toString(){
    CscStrSeeker seeker;
    m_context.iterate(seeker);
    return seeker.toString();
}

CscEditor CscHandler::editor(){
    return CscEditor(m_context);
}

CSC_END