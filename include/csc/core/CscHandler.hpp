#ifndef CSC_CONFIG_HPP
#define CSC_CONFIG_HPP

#include "csc/csc.hpp"
#include "csc/context/Context.hpp"
#include "csc/context/ContextSeeker.hpp"
#include "csc/core/types.hpp"
#include "csc/core/CscEditor.hpp"
#include "csc/core/functions.hpp"
#include "csc/syntax/CommandDrv.hpp"

CSC_BEGIN

class CscHandler{
public:
    using PathItems = decltype(splitPath(""));

public:
    CscHandler() =default;
    CscHandler(ConstStr script);

    bool               accessible(ConstStr path, bool v=false); /* Check if a scope path is accessiable. Check path as variable's path if v is true. */
    CscStr            absolutePath();                                       /* Return a path from root scope to current scope. */
    CscHandler& enter(ConstStr path);                              /* Enter specified scope. Enter root scope if path is only '/' */
    CscHandler& iterate(ContextSeeker &seeker);            /* Iterate current scope, child scope and their variabels. */
    CscStr            toString();                                               /* Convert ever scopes and variables to a string which can be written to '.csc' file directly. */
    CscEditor       editor();                                                  /* Get an editor, which can be used to edit scopes and variables. */

    template<typename Tp>                                            /* Get a specified variable's value in current scope. */
    Tp getValue(ConstStr name);

    template<typename Tp>                                           /* Enter scope then get value. equivalent to enter(prefix).getValue<tp>(name) */
    Tp enterAndGet(ConstStr path);

private:
    Context m_context;
    CommandDrv m_driver;

    bool do_accessible(const PathItems &items, bool v);
    void do_enter(const PathItems &items);
};


//============= Templates =============
template<typename Tp>
inline Tp getValue(ConstStr name){
    throw CscExcept("getValue: Unsupported type.");
}

template<>
inline bool CscHandler::getValue<bool>(ConstStr name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Bool){
        throw CscExcept("getValue: Incompatible type.");
    }

    return value.str == "true" ? true : false;
}

template<>
inline int CscHandler::getValue<int>(ConstStr name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Integer){
        throw CscExcept("getValue: Incompatible type.");
    }

    return static_cast<int>(std::strtol(value.str.c_str(), NULL, baseOf(value.str)));
}

template<>
inline long CscHandler::getValue<long>(ConstStr name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Integer){
        throw CscExcept("getValue: Incompatible type.");
    }

    return std::strtol(value.str.c_str(), NULL, baseOf(value.str));
}

template<>
inline double CscHandler::getValue<double>(ConstStr name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Double){
        throw CscExcept("getValue: Incompatible type.");
    }

    return std::strtod(value.str.c_str(), NULL);
}

template<>
inline CscStr CscHandler::getValue<CscStr>(ConstStr name){
    return m_context.getValue(name).str;
}

template<>
inline array_bool CscHandler::getValue<array_bool>(ConstStr name){
    array_bool array;

    auto values = m_context.getValues(name);
    if(values.type() != ValueType::Bools){
        throw CscExcept("getValue: Incompatible type.");
    }

    for(int i = 1; i < values.size(); i++){
        auto r = values.str(i) == "true" ? true : false;
        array.push_back(r);
    }
}

template<>
inline array_int CscHandler::getValue<array_int>(ConstStr name){
    array_int array;

    auto values = m_context.getValues(name);
    if(values.type() != ValueType::Integers){
        throw CscExcept("getValue: Incompatible type.");
    }

    for(int i = 1; i < values.size(); i++){
        const auto &v = values.str(i);
        auto r = static_cast<int>(std::strtol(v.c_str(), NULL, baseOf(v)));
        array.push_back(r);
    }
}

template<>
inline array_long CscHandler::getValue<array_long>(ConstStr name){
    array_long array;

    auto values = m_context.getValues(name);
    if(values.type() != ValueType::Integers){
        throw CscExcept("getValue: Incompatible type.");
    }

    for(int i = 1; i < values.size(); i++){
        const auto &v = values.str(i);
        auto r = std::strtol(v.c_str(), NULL, baseOf(v));
        array.push_back(r);
    }
}

template<>
inline array_double CscHandler::getValue<array_double>(ConstStr name){
    array_long array;

    auto values = m_context.getValues(name);
    if(values.type() != ValueType::Doubles){
        throw CscExcept("getValue: Incompatible type.");
    }

    for(int i = 1; i < values.size(); i++){
        const auto &v = values.str(i);
        auto r = std::strtol(v.c_str(), NULL, baseOf(v));
        array.push_back(r);
    }
}

template<>
inline array_string CscHandler::getValue<array_string>(ConstStr name){
    array_string array;

    auto values = m_context.getValues(name);
    if(values.type() != ValueType::Strings){
        throw CscExcept("getValue: Incompatible type.");
    }

    for(int i = 1; i < values.size(); i++){
        const auto &v = values.str(i);
        array.push_back(v);
    }
}

template<typename Tp>
inline Tp CscHandler::enterAndGet(ConstStr path){
    const auto &items = detachName(path);
    if(items.second.size() == 0){
        throw CscExcept(std::string("Invalid path: ") + path);
    }

    enter(items.first);
    return getValue<Tp>(items.second);
}

CSC_END
#endif