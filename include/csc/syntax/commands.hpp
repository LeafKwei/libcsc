#ifndef CSC_SYNTAX_COMMANDS_HPP
#define CSC_SYNTAX_COMMANDS_HPP

#include "csc/types.hpp"
#include "csc/context/val.hpp"
#include "csc/syntax/Command.hpp"
CSC_BEGIN

////////////////////////////////////////////////////////////////////////////////////////
inline bool default_runnable(OperandList &operands){ return true; }

////////////////////////////////////////////////////////////////////////////////////////EnterScope
inline void enterscope_run(OperandList &operands, Context &context, ActionCtl &ctl){
    const auto &name = operands.at(0).holder().token().str;
    context.enterScope(name, true);
}

////////////////////////////////////////////////////////////////////////////////////////ExitScope
inline void exitscope_run(OperandList &operands, Context &context, ActionCtl &ctl){
    const auto &name = operands.at(1).holder().token().str;
    if(context.scopeMetaData().name != name){
        throw CommandExcept("Can't exit from a scope, which name is different from current scope.");
    }

    context.leaveScope();
}

////////////////////////////////////////////////////////////////////////////////////////Assign
inline void assign_run(OperandList &operands, Context &context, ActionCtl &ctl){
    const auto &name = operands.at(0).holder().token().str;
    const auto &token = operands.at(2).holder().token();
    auto valtype = valueTypeof(token);

    context.makeVariable(
        name,
        valtype,
        makeValueFrom(token, valtype)
    );
}

////////////////////////////////////////////////////////////////////////////////////////AssignPlural
inline void assginplural_run(OperandList &operands, Context &context, ActionCtl &ctl){
    const auto &name = operands.at(0).holder().token().str;
    auto &holder = operands.at(2).holder();
    auto typebak = ValueType::Unknown;

    for(Size_t idx = 0; idx < holder.size(); idx++){
        auto valtype = valueTypeof(holder.tokenAt(idx));

        /* 处理首个元素时，将其类型赋值给typebak以备后续的类型检查；同时创建一个空的变量 */
        if(idx == 0){
            typebak = valtype;
            context.makeVariable(
                name,
                valtype,
                {}
            );
        }

        /* 数组中的元素类型不一致则抛出异常 */
        if(valtype != typebak){
            throw CommandExcept("ValueType of element in array is not same");
        }

        typebak = valtype;
        context.extendValue(name, makeValueFrom(holder.tokenAt(idx), valtype));
    }
}

////////////////////////////////////////////////////////////////////////////////////////ActionStr
inline void actionstr_run(OperandList &operands, Context &context, ActionCtl &ctl){
    const auto &str = operands.at(1).holder().token().str;
    if(str == "genidx"){
        actionstr_genidx(context, ctl);
    }
    else if(str == "detail"){
        actionstr_detail(context, ctl);
    }
}

inline void actionstr_genidx(Context &context, ActionCtl &ctl){
    ctl.addActionAfter(
        context.scopeMetaData().id,
        
        [](CommandType type, OperandList &operands, Context &context) -> bool {
            return (type == CommandType::EnterScope || type == CommandType::Assign || type == CommandType::AssignPlural);
        },

        [](CommandType type, OperandList &operands, Context &context) -> bool {
            /* 当首次进入一个作用域并且该作用域不存在时，再生成该作用域的索引 */
            if(type == CommandType::EnterScope && !context.probeScope(operands.at(0).holder().token().str)){
                if(!context.probeVariable("_sidx_")){
                    context.makeVariable("_sidx_", ValueType::String, {});
                }
                context.extendValue("_sidx_", operands.at(0).holder().token().str);
                return true;
            }

            /* 生成变量的索引 */
            if(!context.probeVariable(operands.at(0).holder().token().str)){
                if(!context.probeVariable("_vidx_")){
                    context.makeVariable("_vidx_", ValueType::String, {});
                }
                context.extendValue("_vidx_", operands.at(0).holder().token().str);
                return true;
            }

            return false;
        }
    );
}

inline void actionstr_detail(Context &context, ActionCtl &ctl){
        ctl.addActionBefore(0,
        [](CommandType type, OperandList &operands, Context &context) -> bool{
            return true;
        },

        [](CommandType type, OperandList &operands, Context &context) -> bool{
            std::cout << "Command type: " << static_cast<int>(type);
            std::cout << "; Operands: ";
            for(Size_t idx = 0; idx < operands.size(); idx++){
                auto &holder = operands.at(idx).holder();

                if(!holder.empty()){
                    std::cout << operands.at(idx).holder().token().str;
                }

                if(idx < operands.size() - 1) std::cout << ", ";
            }
            std::cout << "; Scope id: " << context.scopeMetaData().id << std::endl;
            return true;
        }
    );
}

CSC_END
#endif