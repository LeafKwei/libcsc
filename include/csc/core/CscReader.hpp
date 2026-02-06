#ifndef CSC_READER_HPP
#define CSC_READER_HPP

#include "csc/types.hpp"
#include "csc/core/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/utility/PathHelper.hpp"
#include "csc/core/functions.hpp"
CSC_BEGIN

class CscReader{
public:
    CscReader(Context &context);
    bool     accessible(const String &path, bool v=false) const; /* 检查给定的路径是否可以访问。当v为true时，路径的最后一部分将被视为变量名称 */
    void     enter(const String &path) const;                               /* 进入给定路径对应的作用域，如果路径为“/”，则进入根作用域 */
    ScoQuerier scoquerier() const;                                              /* 获取当前作用域的查询器以遍历其中的内容 */
    String  toString() const;                                                         /* 从当前作用域开始，将其及子作用域、变量转换为字符串 */

    ////////////////////////////////////////////////////////////////////////////////////////获取变量值的函数模板
    template<typename Tp>
    Tp getValue(const String &name) const;            /* 获取当前作用域下给定名称的非数组变量的值，Tp支持的类型参见文档 */
    template<typename Tp>                            
    Tp getValueDirectly(const String &path) const;  /* 进入指定路径下并获取非数组变量的值(路径的最后一部分作为变量名称) */

    template<typename Tp>                            
    ArrayTp<Tp> getArray(const String &name) const;             /* 获取当前作用域下给定名称的数组变量的值，Ar支持的类型参见文档 */
    template<typename Tp>
    ArrayTp<Tp> getArrayDirectly(const String &path) const;  /* 进入指定路径下并获取数组变量的值(路径的最后一部分作为变量名称) */
    ////////////////////////////////////////////////////////////////////////////////////////

private:
    Context &context_;
    void enterBeforeGet(PathHelper &helper) const;
};

////////////////////////////////////////////////////////////////////////////////////////特例化
/* 通用版本，对于单个值的变量，直接调用toCppValue即可 */
template<typename Tp>
inline Tp CscReader::getValue(const String &name) const{
    const auto &unit = context_.getValueUnit(name);
    return toCppValue<Tp>(unit.value, unit.type);
}

template<typename Tp>                            
inline Tp CscReader::getValueDirectly(const String &path) const{
    PathHelper helper(path);
    enterBeforeGet(helper);
    return getValue<Tp>(helper.basename());
}

/* 对于多个值的变量，需调用getArray*函数 */
template<typename Tp>                             
inline ArrayTp<Tp> CscReader::getArray(const String &name) const{
    ArrayTp<Tp> array;

    auto querier = context_.varquerier(name);
    for(Size_t index = 0; index < querier.size(); index++){
        array.push_back(
            toCppValue<Tp>(querier.value(index), querier.type())
        );
    }

    return array;
}

template<typename Tp>
inline ArrayTp<Tp> CscReader::getArrayDirectly(const String &path) const{
    PathHelper helper(path);
    enterBeforeGet(helper);
    return getArray<Tp>(helper.basename());
}

CSC_END
#endif