#ifndef CSC_CONFIG_HPP
#define CSC_CONFIG_HPP

#include "csc/csc.hpp"
#include "csc/core/CscItem.hpp"
#include "csc/context/Context.hpp"
#include "csc/syntax/CommandDrv.hpp"
CSC_BEGIN

class CscHandler{
public:
    CscHandler() =default;

    void parse(const CscStr &str);
    CscStr toString();

private:
    Context m_context;
    CommandDrv m_driver;
};

CSC_END
#endif