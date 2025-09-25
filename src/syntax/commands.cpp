#include "csc/syntax/commands.hpp"
#include "csc/syntax/functions.hpp"
#include "csc/lex/PureLexer.hpp"
#include "csc/action/types.hpp"
CSC_BEGIN

//============== CommonCmd =============
CommonCmd::CommonCmd(InitOpTypes types) : m_types(types){}

Size_t CommonCmd::sizeofTypes(){
    return m_types.size();
}

CommonCmd::OpType  CommonCmd::opTypeAt(int index){
    return m_types.at(index);
}

//============== EnterScopeCmd =============
EnterScopeCmd::EnterScopeCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator}
){}

bool EnterScopeCmd::runnable(const TokenList &tokens){
    return tokens.at(1).buffer == "::";
}

void EnterScopeCmd::run(const TokenList &tokens, Context &context, ActionCtl &ctl){
    auto &name = tokens.at(0).buffer;
    
    if(context.probeScope(name)){
         context.enterScope(name);
    }
    else{
        ctl.sendAction(ActionType::MakeScope, name, context.scopeMetaData());
        context.makeScope(name, true);
    }
}

//============== ExitScopeCmd =============
ExitScopeCmd::ExitScopeCmd() : CommonCmd(
    {OperandType::Operator, OperandType::Identifier}
){}

bool ExitScopeCmd::runnable(const TokenList &tokens){
    return tokens.at(0).buffer == "::";
}

void ExitScopeCmd::run(const TokenList &tokens, Context &context, ActionCtl &ctl){
    auto &name = tokens.at(1).buffer;

    if(name != context.scopeMetaData().name){
        throw CommandExcept("Can't leave a scope that name is not same to current scope.");
    }

    ctl.sendInnerAction(InnerAction::ExitScope, context.scopeMetaData());
    context.leaveScope();
}

//============== AssignCmd =============
AssignCmd::AssignCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator, OperandType::Value}
){}

bool AssignCmd::runnable(const TokenList &tokens){
    return tokens.at(1).buffer == "=";
}

void AssignCmd::run(const TokenList &tokens, Context &context, ActionCtl &ctl){
    auto vtype = valueTypeof(tokens.at(2));
    if(vtype == ValueType::Unknown) throw CommandExcept("Invalid value in assignment.");

    ctl.sendAction(ActionType::MakeVariable, tokens.at(0).buffer, context.scopeMetaData());
    context.makeVariable(tokens.at(0).buffer, tokens.at(2).buffer, vtype);
}

//============== ArrayAssignCmd =============
ArrayAssignCmd::ArrayAssignCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator, OperandType::Values}
){}

bool ArrayAssignCmd::runnable(const TokenList &tokens){
    return tokens.at(1).buffer == "=";
}

/**
 * token序列中的第三个token即数组字符串，此函数首先会通过数组字符串中的首个元素判断出数组的类型，然后通过PureLexer
 * 依次读取数组字符串中的每个元素，并将其追加到Context的变量中。每个被读入的元素都会被判断类型，如果类型和第一个元素
 * 不同，则视为出错
 */
void ArrayAssignCmd::run(const TokenList &tokens, Context &context, ActionCtl &ctl){
    /* 获取首个元素的类型并将之作为数组的类型 */
    auto vtype = valueTypeof(tokens.at(2));
    if(vtype == ValueType::Unknown) throw CommandExcept("Invalid value in assignment.");
    ctl.sendAction(ActionType::MakeVariable, tokens.at(0).buffer, context.scopeMetaData());
    context.makeVariable(tokens.at(0).buffer, "", vtype);

    auto &name = tokens.at(0).buffer;
    auto etype = ValueType::Unknown;
    CharMngr mngr(tokens.at(2).buffer);
    PureLexer lexer;

    /* 依次读取字符串中的每个元素然后追加到Context的变量中 */
    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);

        if(token.type == TokenType::Aborted){
            break;
        }

        if(token.type == TokenType::Unexcepted){
            if(mngr.getch() ==','){
                mngr.forward();
                continue;
            }
            
            throw CommandExcept("Invalid character in assignment.");
        }

        if(operandTypeof(token) != OperandType::Value){
            throw CommandExcept("Invalid token in assignment.");
        }

        auto cetype = valueTypeof(token);
        if(etype != ValueType::Unknown && etype != cetype){  /* 如果数组中的元素类型不同则视为错误 */
            throw CommandExcept("Elements in array are not a same type.");
        }

        context.extendValues(name, {token.buffer});
        etype = cetype;
    }
}

//============== ActionCmd =============
ActionCmd::ActionCmd() : CommonCmd(
    {OperandType::Keyword, OperandType::Value}
){}

bool ActionCmd::runnable(const TokenList &tokens){
    return (tokens.at(0).buffer == "action") && (tokens.at(1).type == TokenType::String);
}

void ActionCmd::run(const TokenList &tokens, Context &context, ActionCtl &ctl){
    if(tokens.at(1).buffer == "genidx") run_genidx(ctl, context.scopeMetaData().id);
    else throw ActionExcept(String("Unsupport action: ") + tokens.at(1).buffer);
}

void ActionCmd::run_genidx(ActionCtl &ctl, UID scopeid){
    ctl.addActor(
        [](crAction action) -> bool{
            return (action.type() == ActionType::MakeScope) || (action.type() == ActionType::MakeVariable);
        },

        [](crAction action, Context &context) -> bool{
            context.setPostion(action.postion());
            if(action.type() == ActionType::MakeScope){
                if(!context.probeVariable("_sidx_")){
                    context.makeVariable("_sidx_", {std::any_cast<String>(action.extraData())}, ValueType::Strings);
                    return true;
                }
                context.extendValues("_sidx_", {std::any_cast<String>(action.extraData())});
                return true;
            }
            else if(action.type() == ActionType::MakeVariable){
                 if(!context.probeVariable("_vidx_")){
                    context.makeVariable("_vidx_", {std::any_cast<String>(action.extraData())}, ValueType::Strings);
                    return true;
                }
                context.extendValues("_vidx_", {std::any_cast<String>(action.extraData())});
                return true;
            }

            return false;
        },

        scopeid, Livetime::Scoped
    );
}

CSC_END