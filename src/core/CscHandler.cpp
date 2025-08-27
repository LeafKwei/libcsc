#include "csc/core/CscHandler.hpp"
CSC_BEGIN

CscHandler& CscHandler::execute(ConstStr script){

}

CscHandler& CscHandler::enter(ConstStr path){

}

CscHandler& CscHandler::iterate(ContextSeeker &seeker){
    m_context.iterate(seeker);
}

CscStr CscHandler::toString(){

}

CscEditor CscHandler::editor(){

}

CSC_END