**0.7.6**

1.实现了ListScope，对应的枚举为ScopeType::ListScope。现在CscHandler的非类型模板参数可以选择ScopeType::MapScope和ScopeType::ListScope两种，前者基于std::map实现，拥有更快的查找速度，但是对于Scope和Variable的存储顺序是乱序的，这将导致通过toString或iterate等函数遍历Context的内容时无法保证对Scope和Variable遍历顺序与保存它们时的顺序一致；后者基于std::list实现，查找速度较慢，但可以最大程度的保证遍历时顺序与保存时的顺序的一致

**0.7.5**

1.  为了降低Context的复杂度，将Context回滚到了0.7.0版本的实现，同时将对于存储组织的抽象下降到了Scope中，相应的将Scope从纯结构体的实现转换为了一个接口，并添加了MapScope作为基于std::map的Scope实现。添加了factory_makeSharedScope工厂函数根据ScopeType创建对应类型的Scope。
2. 将Context的构造函数改为Context(ScopeType type)，以便可以指定Context创建的Scope种类
3. 将CscHandler的模板参数从`template<typename Ctx, typename =xxx>`改为了`tempalte<ScopeType>`，以便可以在创建CscHandler对象时可以指定其内部的Context的ScopeType

**0.7.3**

1. 为了能通过模板来定制CscHandler中Context的具体实现类型，将原CscHandler的功能拆分到了CscReader和CscWriter(原CscEditor)中，避免特例化getValue系列函数模板时，必须要同时特例化CscHandler和getValue函数的问题。

2. 添加了Context接口，以便后续可以扩展为各类存储组织不同的Context。原Context被重命名为MapContext，保存于csc/context/ctximpl中。

**0.7.0**

1. 由于0.6.9及之前的版本存在一个无法忽视的问题——Lexer解析数组时，如果数组的元素是字符串，并且字符串中含有`}`时，相关的Reader将无法获取到正确的数组边界，从而导致token读取出错，因此在0.7.0版本中，重构了包括Lexer、TokenReader在内的诸多内容。因为Token属于底层组件，因此重构时也影响到了诸多上层组件，主要包括command目录下的commands、CmdExecutor。相应的，添加了TokenHolder作为中间层，并以此提供了对数组等由多个token组成的复杂token的访问能力。
2. 将Command和TokenReader全部由旧版本的类继承更改为了function实现，使之更加简洁清晰
3. 添加了TokenPool用于缓存Token/TokenHolder，现在CmdDriver会在script被全部分解为Token后再进行命令处理，可以更早地报告出非法Token

**0.6.9**

1. 重构了action模块，将原本的发送Action+处理Action的事件处理模式改变为了通过检测Command及Operand触发的模式
2. 添加了CommandExecutorAgent以及初始化CmdExecutor的初始化器stdexec_initializer
2. 添加了关键字`action "detail"`，用于打印解析过程中执行的命令信息

**0.6.8**

1. 将CscWriter对int和const char*的特殊处置方式从模板特例化转变为了可变参数+函数模板重载
2. 重命名了一些using别名

**0.6.5**

1. 将Context底层的数据保存单位从std::string更改为了std::any，为了避免类型转换错误，请确保保存到Context中的值与ValueType相匹配
2. 添加了CppType模板用于将ValueType映射为对应的C++内置类型(如bool、long)
3. 添加了Operand和ValueMaker，负责将Token转换为可供CmdExecutor和Context使用的对象
4. 将PureLexer的TokenReader添加方式从内部输入转换为外部输入，并提供了对应的initializer函数用以初始化，同时引入了LexerAgent作为友元，以便在不添加public函数的情况下让外部函数可以向PureLexer添加TokenReader
5. 重命名了一些using别名

**0.6.1**

1. 添加了action模块
2. 重新设计了syntax，添加了CmdExecutor用于缓存Token及执行Command
3. 新增关键字`action "genidx"`，可为作用域和变量生成索引

**0.5.3**

1. 添加了Context::scopeID函数，用于获取当前Scope的ID
2. Bug修复：修复了Context在创建或clean后，根作用域的ID字段未被赋值的问题

**0.5.2**

1. 为Scope添加了ID字段，现在每个Scope都拥有了唯一的标识

**0.5.1**

1. Bug修复：更新了lex/readers中的NumberReader，现在Lexer可以识别十进制数字前方的`+-`前缀

**0.5.0**

1. 首次发布的版本，完成了libcsc的基本功能