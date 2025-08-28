#include "csc/core/CscHandler.hpp"
#include "csc/core/CscStrSeeker.hpp"
CSC_BEGIN

CscHandler::CscHandler(ConstStr script){
    m_driver.drive(script, m_context);
}

CscHandler& CscHandler::enter(ConstStr path){
    const auto &items = splitPath(path);
    if(items.size() == 0){
        throw CscExcept(std::string("Invalid path: ") + path);
    }

    for(int index = 0; index < items.size(); index++){
        const auto &item = items.at(index);
        if(index == 0 && item == "/"){             //If path is absolute, go to root scope.
            m_context.restart();
            continue;
        }

        if(item.size() == 0){
            throw CscExcept(std::string("Invalid path: ") + path);
        }

        m_context.enterScope(item);
    }

    return *this;
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