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