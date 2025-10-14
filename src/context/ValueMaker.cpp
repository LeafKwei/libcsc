#include "csc/lex/Lexer.hpp"
#include "csc/lex/initializers.hpp"
#include "csc/context/types.hpp"
#include "csc/context/ValueMaker.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

ValueMaker::ValueMaker(const Token &token){
    make(token);
}

ValueType ValueMaker::type() const noexcept{
    return m_unit.type;
}

Value ValueMaker::value() const noexcept{
    return m_unit.value;
}

Value ValueMaker::make(const Token &token){
    m_unit.type = (token.type != TokenType::Array) ? getValueTypeof(token) : getArrayValueTypeof(token);
    m_unit.value = getValueof(token);
    return m_unit.value;
}

Value ValueMaker::makeZero(ValueType type){
    switch(type){
        case ValueType::Bool:
            return CppType<ValueType::Bool>::type{};
        case ValueType::Integer:
            return CppType<ValueType::Integer>::type{};
        case ValueType::Double:
            return CppType<ValueType::Double>::type{};
        case ValueType::String:
            return CppType<ValueType::String>::type{};
        default:
            return Value{};
    }
}

Value ValueMaker::getValueof(const Token &token){
    switch(m_unit.type){
        case ValueType::Bool:
            if(token.str == "true") return CppType<ValueType::Bool>::type{true};
            return CppType<ValueType::Bool>::type{false};
        //------------------------------------------------------
        case ValueType::Integer:
            if(token.tag == TokenTag::Hex){                        //当Token含有16进制标签时，按16进制转换
                return CppType<ValueType::Integer>::type{
                    strtol(token.str.c_str(), NULL, 16)};
            }
            return  CppType<ValueType::Integer>::type{     //否则按10进制转换
                    strtol(token.str.c_str(), NULL, 10)};
        //------------------------------------------------------
        case ValueType::Double:
            return CppType<ValueType::Double>::type{strtod(token.str.c_str(), NULL)};
        //------------------------------------------------------
        case ValueType::String:
            return CppType<ValueType::String>::type{token.str};
        //------------------------------------------------------
        default:
            return Value{};
    }
}

ValueType ValueMaker::getValueTypeof(const Token &token) const{
        switch(token.type){
        case TokenType::Keyword:
            return (isBoolString(token.str)) ? ValueType::Bool : ValueType::Unknown;
        case TokenType::Number:
            return (token.tag == TokenTag::Float) ? ValueType::Double : ValueType::Integer;
        case TokenType::String:
            return ValueType::String;
        default:
            return ValueType::Unknown;
    }
}

ValueType ValueMaker::getArrayValueTypeof(const Token &token) const{
    CharMngr mngr(token.str);
    PureLexer lexer;
    arraylexer_initializer(lexer);

    const auto &tk = lexer.nextResultFrom(mngr);
    return getValueTypeof(tk.token);
}

CSC_END