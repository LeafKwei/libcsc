#ifndef CSC_WALKER_HPP
#define CSC_WALKER_HPP

#include <vector>
#include "csc/context/Querier.hpp"
#include "csc/context/Scope.hpp"
CSC_BEGIN

/* Walker用于迭代指定Scope下的所有变量和子Scope  */
class Walker{
public:
    Walker(ScopePtr scop);
    Walker(ScopePos pos);

    bool         noscopes() const;              /* 此Scope不存在子Scope */
    bool         novariables() const;           /* 此Scope不存在变量 */
    String       name() const;                   /* 获取Walker当前所在的Scope名称 */
    void          startScopeWalk();              /* 开启Scope的迭代 */
    void          startVariableWalk();          /* 开启变量的迭代 */
    bool          hasNextScope() const;       /* 是否存在下一个Scope可迭代 */
    bool          hasNextVariable() const;    /* 是否存在下一个变量可迭代 */
    Walker      nextScope();                       /* 获取下一个Scope的漫步器 */
    Querier     nextVariable();                    /* 获取下一个变量的查询器 */

private:
    Size_t scoindex_;
    Size_t varindex_;
    Size_t scosize_;
    Size_t varsize_;
    ScopeWptr scope_;
    
    ScopePtr lockScopePtr() const;
};

CSC_END
#endif