#ifndef CSC_DETECTOR_HPP
#define CSC_DETECTOR_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

/* Detector可帮助外部快速确定是否存在指定的scope和variable */
class Detector{
public:
    Detector(ScopeWkr wkr);

    bool tryEnter(crString name);            //进入指定名称的scope(更新m_ptr)，如果不存在则返回false
    bool detect(crString name);              //检查当前scope下是否存在指定名称的scope或variable
    bool detectScope(crString name);    //检查当前scope下是否存在指定名称的scope
    bool detectVariable(crString name); //检查当前scope下是否存在指定名称的variable

private:
    ScopeWkr ptr_;

    void assertValidPtr() const noexcept;
};

CSC_END
#endif