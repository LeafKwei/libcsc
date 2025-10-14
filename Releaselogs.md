**0.6.8**

1. 将CscEditor对int和const char*的特殊处置方式从模板特例化转变为了可变参数+函数模板重载
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