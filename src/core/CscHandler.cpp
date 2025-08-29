#include "csc/core/CscHandler.hpp"
#include "csc/core/CscStrSeeker.hpp"
CSC_BEGIN

CscHandler::CscHandler(ConstStr script){
    m_driver.drive(script, m_context);
}

bool CscHandler::accessible(ConstStr path, bool v){
    return v ? do_accessibleVariable(path) : do_accessibleScope(path);
}

CscStr CscHandler::absolutePath(){
    return CscStr("/") + m_context.relation("/");
}

CscHandler& CscHandler::enter(ConstStr path){
    const auto &items = splitPath(path);
    if(items.size() == 0){
        throw CscExcept(std::string("Invalid path: ") + path);
    }

    try{
        do_enter(items);
    }
    catch(ContextExcept &e){
        throw CscExcept(std::string("Invalid path: ") + path);
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

bool CscHandler::do_accessibleScope(ConstStr path){
    auto result = true;
    const auto pos = m_context.postion();
    
    try{
        enter(path);
    }
    catch(CscExcept &e){
        result = false;
    }

    m_context.setPostion(pos);
    return result;
}

bool CscHandler::do_accessibleVariable(ConstStr path){
    auto result = true;
    const auto &items = detachName(path);
    const auto pos = m_context.postion();

    if(items.first.size() != 0){      //If scope path is not empty.
        try{
            enter(items.first);
        }
        catch(CscExcept &e){
            m_context.setPostion(pos);
            return false;
        }
    }

    if(!m_context.probeVariable(items.second)){
        result = false;
    }

    m_context.setPostion(pos);
    return result;
}

void CscHandler::do_enter(const PathItems &items){
    for(int index = 0; index < items.size(); index++){
        const auto &item = items.at(index);
        if(index == 0 && item == "/"){             //If path is absolute, go to root scope.
            m_context.restart();
            continue;
        }
    
        m_context.enterScope(item);
    }
}

CSC_END