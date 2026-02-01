#ifndef CSC_SYNTAX_COMMANDS_HPP
#define CSC_SYNTAX_COMMANDS_HPP

#include "csc/types.hpp"
#include "csc/context/val.hpp"
#include "csc/syntax/Command.hpp"
#include "csc/utility/PathHelper.hpp"
CSC_BEGIN

////////////////////////////////////////////////////////////////////////////////////////
inline bool default_runnable(OperandList &operands){ return true; }
inline void default_run(OperandList &operands, Context &context, ActionCtl &ctl){}

////////////////////////////////////////////////////////////////////////////////////////VoidCmd
inline bool voidcmd_runnable(OperandList &operands){ return true; }
inline void voidcmd_run(OperandList &operands, Context &context, ActionCtl &ctl){}

////////////////////////////////////////////////////////////////////////////////////////EnterScope
inline void enterscope_run(OperandList &operands, Context &context, ActionCtl &ctl){
    const auto &name = operands.at(0).stringvalue();
    context.enterScope(name, true);
}

////////////////////////////////////////////////////////////////////////////////////////ExitScope
inline void exitscope_run(OperandList &operands, Context &context, ActionCtl &ctl){
    const auto &name = operands.at(1).stringvalue();
    if(context.scopeinf().name != name){
        throw CommandExcept("Can't exit from a scope, which name is different from current scope.");
    }

    context.leaveScope();
}

////////////////////////////////////////////////////////////////////////////////////////Assign
inline void assign_run(OperandList &operands, Context &context, ActionCtl &ctl){
    const auto &name = operands.at(0).stringvalue();
    const auto &unit = operands.at(2).refervalue();

    context.makeVariable(
        name,
        unit.type,
        unit.value
    );
}

////////////////////////////////////////////////////////////////////////////////////////AssignPlural
inline void assginplural_run(OperandList &operands, Context &context, ActionCtl &ctl){
    const auto &name = operands.at(0).stringvalue();
    auto &operand = operands.at(2);
    auto typebak = ValueType::Unknown;

    for(Size_t idx = 0; idx < operand.size(); idx++){
        const auto &unit = operand.refervalue(idx);
        /* 处理首个元素时，将其类型赋值给typebak以备后续的类型检查；同时创建一个空的变量 */
        if(idx == 0){
            typebak = unit.type;
            context.makeVariable(
                name,
                unit.type,
                {}
            );
        }

        /* 数组中的元素类型不一致则抛出异常 */
        if(unit.type != typebak){
            throw CommandExcept("ValueType of element in array is not same");
        }

        typebak = unit.type;
        context.extendValue(name, unit.value);
    }
}

////////////////////////////////////////////////////////////////////////////////////////GotoStr
inline void gotostr_run(OperandList &operands, Context &context, ActionCtl &ctl){
    PathHelper helper;
    helper.decompose(operands.at(1).stringvalue());

    /* 如果不是绝对路径或路径为空，则不执行任何操作 */
    if((!helper.valid()) || (!helper.absolute())){
        return;
    }

    /* 将Context切换到指定路径 */
    context.restart();
    auto size = helper.size();
    for(decltype(size) i = 0; i < size; i++){
        context.enterScope(helper.element(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////ActionStr
inline void actionstr_genidx(Context &context, ActionCtl &ctl){
    ctl.addActionAfter(
        context.scopeinf().id,
        
        [](CommandType type, OperandList &operands, Context &context) -> bool {
            return (type == CommandType::EnterScope || type == CommandType::Assign || type == CommandType::AssignPlural);
        },

        [](CommandType type, OperandList &operands, Context &context) -> bool {
            /* 当首次进入一个作用域并且该作用域不存在时，再生成该作用域的索引 */
            if(type == CommandType::EnterScope && !context.hasScope(operands.at(0).stringvalue())){
                if(!context.hasVariable("_sidx_")){
                    context.makeVariable("_sidx_", ValueType::String, {});
                }
                context.extendValue("_sidx_", operands.at(0).stringvalue());
                return true;
            }

            /* 生成变量的索引 */
            if(!context.hasVariable(operands.at(0).stringvalue())){
                if(!context.hasVariable("_vidx_")){
                    context.makeVariable("_vidx_", ValueType::String, {});
                }
                context.extendValue("_vidx_", operands.at(0).stringvalue());
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
                std::cout << operands.at(idx).stringvalue();
                if(idx < operands.size() - 1) std::cout << ", ";
            }
            std::cout << "; Scope id: " << context.scopeinf().id << std::endl;
            return true;
        }
    );
}

inline void actionstr_run(OperandList &operands, Context &context, ActionCtl &ctl){
    const auto &str = operands.at(1).stringvalue();
    if(str == "genidx"){
        actionstr_genidx(context, ctl);
    }
    else if(str == "detail"){
        actionstr_detail(context, ctl);
    }
}

CSC_END
#endif