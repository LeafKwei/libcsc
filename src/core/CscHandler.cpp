#include "csc/core/CscHandler.hpp"
#include "csc/core/CscStrSeeker.hpp"
CSC_BEGIN

CscHandler::CscHandler(ConstStr script){
    m_driver.drive(script, m_context);
}

bool CscHandler::accessible(ConstStr path, bool v=true){
    auto result = true;
    const auto &items = splitPath(path);
    const auto backup = m_context.postion();

    if(items.size() < 1) return false;
    result = do_accessible(items, v);
    m_context.setPostion(backup);
    return result;
}

CscStr CscHandler::absolutePath(){
    return CscStr("/") + m_context.relation("/");
}

CscHandler& CscHandler::enter(ConstStr path){
    const auto &items = splitPath(path);
    if(items.size() == 0){
        throw CscExcept(std::string("enter: Invalid path: ") + path);
    }

    do_enter(items);
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

bool CscHandler::do_accessible(const PathItems &items, bool v){
    auto result = true;

    for(int index = 0; index < items.size(); index++){
        const auto &item = items.at(index);

        if(index == 0 && item == "/"){
            m_context.restart();
            continue;
        }

        if(v && (index == (items.size() - 1))){      //If last item is a variable's name.
            if(!m_context.probeVariable(item)){
                result = false;
                break;
            }
            continue;
        }

        if(!m_context.probeScope(item)){
           result = false;
           break;
        }

        enter(item);
    }
}

void CscHandler::do_enter(const PathItems &items){
    for(int index = 0; index < items.size(); index++){
        const auto &item = items.at(index);
        if(index == 0 && item == "/"){             //If path is absolute, go to root scope.
            m_context.restart();
            continue;
        }

        if(!m_context.probeScope(item)){
            throw CscExcept(std::string("enter: Invalid path item: ") + item);
        }

        m_context.enterScope(item);
    }
}

CSC_END