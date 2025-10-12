#include "csc/syntax/commands.hpp"
#include "csc/syntax/functions.hpp"
#include "csc/lex/PureLexer.hpp"
#include "csc/lex/initializers.hpp"
#include "csc/action/types.hpp"
CSC_BEGIN

//============== CommonCmd =============
CommonCmd::CommonCmd(InitTokens tokens){
    genKey(tokens);
}

crString CommonCmd::key(){
    return m_key;
}

/* 派生类通过构造函数将一组Token传递给CommonCmd，后者将每个token转换为key item，并最终生成一个key */
void CommonCmd::genKey(InitTokens tokens){
    String key("");

    for(const auto &token : tokens){
        key.append(tokenToKeyItem(token)).append("_");
    }

    key.pop_back();  //删除末尾多余的_
    m_key = key;
}

//============== EnterScopeCmd =============
EnterScopeCmd::EnterScopeCmd() : CommonCmd(
    {
        {TokenType::Identifier, TokenTag::None, ""},
        {TokenType::Operator, TokenTag::None, "::"}
    }
){}

bool EnterScopeCmd::runnable(crOperandList operands){
    return true;
}

void EnterScopeCmd::run(crOperandList operands, Context &context, ActionCtl &ctl){
    auto &name = operands.at(0).str();
    
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
    {
        {TokenType::Operator, TokenTag::None, "::"},
        {TokenType::Identifier, TokenTag::None, ""}
    }
){}

bool ExitScopeCmd::runnable(crOperandList operands){
    return true;
}

void ExitScopeCmd::run(crOperandList operands, Context &context, ActionCtl &ctl){
    auto &name = operands.at(1).str();
    if(name != context.scopeMetaData().name){
        throw CommandExcept("Can't leave a scope that name is not same to current scope.");
    }

    ctl.sendInnerAction(InnerAction::ExitScope, context.scopeMetaData());
    context.leaveScope();
}

//============== AssignCmd =============
AssignCmd::AssignCmd() : CommonCmd(
    {
        {TokenType::Identifier, TokenTag::None, ""},
        {TokenType::Operator, TokenTag::None, "="},
        {TokenType::String, TokenTag::None, ""}              //OperandType::Value可以由TokenType::Number、Bool、String等转换，所以此处可以任意填写其中一个
    }
){}

bool AssignCmd::runnable(crOperandList operands){
    return true;
}

void AssignCmd::run(crOperandList operands, Context &context, ActionCtl &ctl){
    auto vtype = operands.at(2).typeofValue();
    if(operands.at(2).typeofValue() == ValueType::Unknown) throw CommandExcept("Invalid value in assignment.");

    ctl.sendAction(
        ActionType::MakeVariable, 
        operands.at(0).str(),
        context.scopeMetaData()
    );
    context.makeVariable(
        operands.at(0).str(),
        operands.at(2).value(),
        vtype
    );
}

//============== ArrayAssignCmd =============
ArrayAssignCmd::ArrayAssignCmd() : CommonCmd(
    {
        {TokenType::Identifier, TokenTag::None, ""},
        {TokenType::Operator, TokenTag::None, "="},
        {TokenType::Array, TokenTag::None, ""}
    }
){}

bool ArrayAssignCmd::runnable(crOperandList operands){
    return true;
}

/**
 * token序列中的第三个token即数组字符串，此函数首先会通过数组字符串中的首个元素判断出数组的类型，然后通过PureLexer
 * 依次读取数组字符串中的每个元素，并将其追加到Context的变量中。每个被读入的元素都会被判断类型，如果类型和第一个元素
 * 不同，则视为出错
 */
void ArrayAssignCmd::run(crOperandList operands, Context &context, ActionCtl &ctl){
    /* 获取数组的类型 */
    auto atype = operands.at(2).typeofValue();
    if(atype == ValueType::Unknown) throw CommandExcept("Invalid value in assignment.");
    ctl.sendAction(
        ActionType::MakeVariable, 
        operands.at(0).str(),
        context.scopeMetaData()
    );
    context.makeVariable(       //创建一个空变量
        operands.at(0).str(),
        {},
        atype
    );

    auto &name = operands.at(0).str();
    CharMngr mngr(operands.at(2).str());
    PureLexer lexer;
    arraylexer_initializer(lexer);

    /* 依次读取字符串中的每个元素然后追加到Context的变量中 */
    while(mngr.valid()){
        const auto &result = lexer.nextResultFrom(mngr);
        Operand op(result.token);

        if(result.hint == LexHint::Aborted){  //没有可读取的token时结束循环
            break;
        }

        if(op.typeofToken() == TokenType::Unknown){
            /* 出现不可识别的字符时，如果是“,”则跳过，否则抛出异常 */
            if(mngr.getch() ==','){
                mngr.forward();
                continue;
            }
            
            throw CommandExcept("Invalid character in assignment.");
        }

        if(op.typeofOperand() != OperandType::Value){
            throw CommandExcept("Invalid token in assignment.");
        }

        auto tp = op.typeofValue();
        if(tp != atype){    //如果数组中的元素类型不同则视为错误
            throw CommandExcept("Elements in array are not a same type.");
        }

        context.extendValues(name, {op.value()});
    }
}

//============== ActionCmd =============
ActionCmd::ActionCmd() : CommonCmd(
    {
        {TokenType::Keyword, TokenTag::None, KW_ACTION},
        {TokenType::String, TokenTag::None, ""}
    }
){}

bool ActionCmd::runnable(crOperandList operands){
    return operands.at(1).typeofValue() == ValueType::String;
}

void ActionCmd::run(crOperandList operands, Context &context, ActionCtl &ctl){
    if(operands.at(1).str() == "genidx") run_genidx(ctl, context.scopeMetaData().id);
    else throw ActionExcept(String("Unsupport action: ") + operands.at(1).str());
}

/**
 * 关键字：action "genidx"
 * 在当前作用域中创建两个内部变量“_sidx_”、“_vidx_”，并且将此作用域中随后读取的子作用域名称保存到_sidx_，变量名称保存到_vidx_，
 * 供迭代使用
 */
void ActionCmd::run_genidx(ActionCtl &ctl, UID scopeid){
    ctl.addActor(
        [](crAction action) -> bool{
            return (action.type() == ActionType::MakeScope) || (action.type() == ActionType::MakeVariable);
        },

        [](crAction action, Context &context) -> bool{
            context.setPostion(action.postion());
            if(action.type() == ActionType::MakeScope){
                if(!context.probeVariable("_sidx_")){
                    context.makeVariable("_sidx_", {std::any_cast<String>(action.extraData())}, ValueType::String);
                    return true;
                }
                context.extendValues("_sidx_", {std::any_cast<String>(action.extraData())});
                return true;
            }
            else if(action.type() == ActionType::MakeVariable){
                 if(!context.probeVariable("_vidx_")){
                    context.makeVariable("_vidx_", {std::any_cast<String>(action.extraData())}, ValueType::String);
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