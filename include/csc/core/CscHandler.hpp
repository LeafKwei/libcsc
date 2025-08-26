#ifndef CSC_CONFIG_HPP
#define CSC_CONFIG_HPP

#include "csc/csc.hpp"
#include "csc/context/Context.hpp"
#include "csc/context/ContextSeeker.hpp"
#include "csc/core/types.hpp"
#include "csc/core/CscEditor.hpp"
#include "csc/syntax/CommandDrv.hpp"

CSC_BEGIN

class CscHandler{
public:
    CscHandler() =default;

    CscHandler& execute(ConstStr &script);
    CscHandler& enter(ConstStr &path);
    CscHandler& iterate(ContextSeeker &seeker);
    CscStr toString();
    CscEditor editor();

    template<typename Tp>
    Tp getValue(ConstStr &path);

    template<typename Tp>
    Tp enterAndGet(ConstStr &path);

private:
    Context m_context;
    CommandDrv m_driver;
};


//============= Templates =============
template<>
bool CscHandler::getValue<bool>(ConstStr &path){

}

template<>
int CscHandler::getValue<int>(ConstStr &path){

}

template<>
long CscHandler::getValue<long>(ConstStr &path){

}

template<>
double CscHandler::getValue<double>(ConstStr &path){

}

template<>
CscStr CscHandler::getValue<CscStr>(ConstStr &path){

}

CSC_END
#endif