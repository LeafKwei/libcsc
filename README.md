# 1.简介

libcsc是使用C++实现的一个工具库，用于解析后缀为`.csc`(Command-Style Configuration)的配置文件。



# 2.csc文件语法

## 2.1.基本语法

csc文件的语法十分简单，在当前版本中，csc文件由两部分组成：作用域(Scope)和变量(Variable)。以下是一个csc文件*sample.csc*的示例：

```
name = "CSC Sample"
version = "0.8.0"

;This is a scope
Dummy::
	switch = true
	factor = 1.15
	maxCount = 255
	minCount = 0xF0
	users = {"Tom", "Jerry", "Emily"}

	Bar::
		content = "Anyting"
	::Bar
::Dummy
```

在该文件中，形如`name = "CSC Sample"`声明了一个变量，`name`是变量名称，`"CSC Sample"`是变量值，csc文件支持以下类型的变量：

* 布尔值：true、false
* 整型：255、0xFF、+1、-1
* 浮点型：1.15
* 字符串："CSC Sample"
* 数组：{"A", "B", "C"}、{1, 2, 3}

对于数组而言，其中的所有元素都需要是相同的类型。当字符串中需要出现引号`"`这类特殊字符时，可以使用`\`进行转义。

然后，`Dummy::`声明了一个作用域，`Dummy`是作用域名称，不同作用域内的同名变量相互独立，如果在同一个作用域内声明相同的变量，那么后者将覆盖前者。作用域内允许声明另一个作用域，就像`Bar::`一样。在作用域中完成所有变量的声明后，需要使用`::Dummy`和`::Bar`表示退出该作用域。在本例中，像`name = "CSC Sample"`这类没有声明于用户定义的作用域内的变量，将默认处于根作用域中。

csc文件支持注释，注释以分号`;`开始，在分号之后的内容都被视为注释内容而被忽略。此外，csc的语法较为宽松，只要使用合适的分隔符(例如空白)，csc文件的内容甚至可以压缩到一行：

```
name = "CSC Sample" version = "0.8.0" Dummy:: switch = true factor = 1.15 maxCount = 255 minCount = 0xF0 users = {"Tom", "Jerry", "Emily"} Bar:: content = "Anyting" ::Bar ::Dummy
```



## 2.2.数组

在前一节我们已经提到过了数组，在libcsc中，数组被作为具有多个值的变量而实现，由于libcsc要求一个变量必须有值，因此，空数组是不被允许的：

```
array = {}  ;将导致断言失败
```

此外，如果数组仅具有一个元素，那么当使用toString函数时，对应的变量将被还原为单个值的变量：

```
;原内容
array = {"Hello"}

;toString生成的内容
array = "Hello"
```



## 2.3.占位

有时我们可能想要在配置文件的某个位置先用一个变量占位，然后在未来的某个时间段再设置变量的值，为此，libcsc提供了关键字`void`，它可用在变量的赋值中，例如：

```
holder = void
```

被赋予void的变量将在命令匹配与执行阶段被忽略，相应的，此类变量在toString函数返回的结果中也不会表现出来。



# 3.使用方式

## 3.1.编译

(本例以Win10、MinGW作为编译环境，请确保已安装CMake和make)

libcsc使用CMake作为构建系统，为了不破坏项目原有结构，本例以源外构建为例。假设libcsc项目位于*D:\File\libcsc*，我们先于同级目录创建一个*build*目录，即*D:\File\build*，随后进入build目录，执行：

```shell
cmake -G "Unix Makefiles" ../libcsc
```

待生成Makefile文件后，执行`make`。在编译成功后，可以在*build/bin/static*目录下找到编译后的静态库。如果需要编译动态链接库，则在执行cmake命令时添加如下参数：

```shell
cmake -DBUILD_SHARED_LIBS=YES -G "Unix Makefiles" ../libcsc
```

然后同样是执行`make`。编译后在*build/bin/dll*目录下可找到动态链接库。



## 3.2.使用

以解析sample.csc为例，让我们编写如下程序，并保存为*main.cpp*：

```C++
#include <iostream>
#include <fstream>
#include "csc/core/CscHandler.hpp"
#include "csc/context/Context.hpp"

using csc::String;
using csc::Context;
using csc::ScopeType;
using csc::CscReader;
using csc::CscHandler;

int main(void){
    //使用标准库函数读入文件内容到字符串
	std::ifstream ifs("sample.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    
    //创建CscHandler对象，解析文件内容，随后通过reader函数获取到reader对象，开始读取文件内容
    //通过指定不同的ScopeType作为模板参数，可以定制CscHandler对于csc配置内容的存储组织
    CscHandler<ScopeType::MapScope> handler(str);
    CscReader reader = handler.reader();  //获取一个reader对象用于读取配置内容
    reader.enter("/");                    //进入根作用域
    std::cout << "name: " << reader.getValue<String>("name") << std::endl;        //获取name变量值
    reader.enter("/Dummy");              //进入根作用域下的Dummy作用域
    std::cout << "Dummy.switch: " << reader.getValue<bool>("switch") << std::endl;//获取Dummy::switch
    
    //也可以使用getValueDirectly函数直接进入/Dummy作用域并获取变量switch
	std::cout << reader.getValueDirectly<bool>("/Dummy/switch") << std::endl;
}
```

假设*main.cpp*所在项目结构如下：

```
/
---include
------csc
---lib
------libcsc.a
---src
------main.cpp
------sample.csc
```

其中，include目录下包含了libcsc的所有头文件。我们进入src，然后执行如下命令编译main.cpp：

```shell
g++ -I ../include -L ../lib -o main main.cpp -lcsc
```

最后执行编译得到的main.exe即可。



# 4.API文档

## 4.1.用户使用的API

以下内容将对**csc/core**下的用户API进行详细说明：

### CscHandler

CscHandler可用于解析csc文件内容并获取其中的变量值，用户需要将保存有csc文件内容的字符串作为构造函数参数交给CscHandler进行解析(在创建CscHandler对象后也可以使用handle函数解析)。CscHandler亦可用于创建csc文件的内容，用户通过默认构造函数创建一个空的CscHandler对象，然后通过writer函数获取到writer对象，随后就可根据自身需要创建作用域及相应的变量，最后调用reader函数获取CscReader，使用其中的toString函数将之前创建的作用域和变量转换为字符串，将字符串写入文件即可。

自0.7.6版本后，创建CscHandler对象时需要指定一个ScopeType类型的枚举值作为模板参数，该枚举值将影响内部的Context对象使用的作用域(Scope)类型，不同类型的作用域会使用不同的方式组织和存储变量和子作用域，将会影响到toString时生成的字符串中变量和作用域的位置关系，ScopeType的可选值和作用域参见附录-作用域类型。

```C++
CscHandler()
    默认构造函数，创建一个带有根作用域的空CscHandler对象，通常结合editor函数和toString函数来创建csc文件的内容
CscHandler(const String &script)
    按csc语法解析script中的内容到CscHandler对象中
int handle(const String &script)
	按csc语法解析script中的内容到CscHandler对象中，返回执行的命令数量
CscReader reader()
    获取一个用于读取csc配置内容的CscReader对象，与CscHandler共享一个Context
CscWriter writer()
    获取一个用于写入csc配置内容的CscWriter对象，与CscHandler共享一个Context
```

### CscReader

CscReader提供了对csc配置内容的读取功能。

```c++
bool accessible(const String &path, bool v=false)
    检查给定的路径是否可以访问。当v为true时，路径的最后一部分将被视为变量名称检查
void enter(const String &path)
	进入给定路径对应的作用域，如果路径为“/”，则进入根作用域
ScoQuerier scoquerier()
    为当前作用域生成一个查询器对象以遍历其中的内容
String toString()
    从当前作用域开始，将其及子作用域、变量转换为字符串

template<typename Tp>
Tp getValue(const String &name)
    获取当前作用域下名称为name的变量值，并将其转换为Tp类型，此函数适用于非数组变量，如果变量是具有多个值的数组，需要使用
    getArray*族函数。模板参数Tp支持的类型参考附录-支持类型
template<typename Tp>                            
Tp getValueDirectly(const String &path)
    进入指定的路径下获取对应的变量值，并将其转换为Tp类型，路径的最后一部分(basename)被作为变量名称使用(例如/a/b的b被视
    为变量名称)
template<typename Tp>                            
ArrayTp<Tp> getArray(const String &name)
    与getValue类似，用于获取具有多个值的数组变量
template<typename Tp>
ArrayTp<Tp> getArrayDirectly(const String &path)
    与getValueDirectly类似，用于获取具有多个值的数组变量
```

### CscWriter

CscWriter提供了对csc配置内容的编辑功能。

```C++
CscWriter& autoEnterOn()
	开启autoEnter功能，当使用makeScope函数创建作用域后，自动进入该作用域而无需调用enterScope函数
CscWriter& autoEnterOff()
	关闭autoEnter功能
CscWriter& makeScope(const String &name)
	在当前作用域下创建一个指定名称的作用域
CscWriter& enterScope(const String &name)
	进入当前作用域下指定名称的子作用域
CscWriter& leaveScope()
	离开当前作用域，回到它的父作用域。当位于根作用域时，调用此函数将引发异常
CscWriter& cleanScope(const String &name)
	清除当前作用域下指定名称的作用域
CscWriter& makeVariable(const String &name, T &&...values)
	在当前作用域中创建指定名称的变量，values是一组指定变量值的可变参数，请确保其都为同一类型
    当创建一个已存在的变量时，将会直接使用values替代该变量中的变量值
    makeVariable在0.7.8版本后可根据变量值自动推断变量的ValueType类型
CscWriter& extendValues(const String &name, T &&...values)
	追加当前作用域中指定名称的变量的变量值
CscWriter& cleanVariable(const String &name)
	清除当前作用域中指定名称的变量
```

### CscString

借助ScoQuerier对象(即作用域查询器对象)递归遍历作用域，将其中的内容转换为字符串

```c++
CscString()
	默认构造函数，创建一个内容为空的CscString对象
CscString(ScoQuerier querier, bool isroot)
   	遍历指定的querier并生成字符串，如果isroot参数为true，则代表querier对象来自根作用域，这会使得该作用域的名称不会出现在
    字符串中
String localstr()
    获取上一次生成字符串时缓存的的字符串对象
String strfrom(ScoQuerier querier, bool isroot)
    遍历指定的querier并生成字符串，如果isroot参数为true，则代表querier对象来自根作用域，这会使得该作用域的名称不会出现在
    字符串中
```

### VarQuerier

查询变量的相关信息，用于遍历拥有多个值的变量(即数组变量)的每个值

```C++
VarQuerier(VariablePtr varp)
    以给定的变量指针创建一个查询器对象
String name()
    获取变量名称
ValueType type()
    获取变量类型
Size_t size()
    获取变量的值的数量
Value value(int index=0)
    获取指定位置的变量值
ValueUnit valueunit(int index=0)
    获取指定位置的变量值和类型构成的变量单元
```

### ScoQuerier

遍历作用域的内容

```c++
ScoQuerier(ScopePtr scop)
    以给定的作用域指针创建一个漫步器对象
ScoQuerier(ScopePos pos)
    以给定的作用域位置创建一个漫步器对象
bool noscopes()
    此作用域中是否不存在子作用域
bool novariables()
    此作用域中是否不存在变量
String name()
    获取此作用域名称
Size_t sizeofVariables()
    获取此作用域中的变量数量
Size_t sizeofScopes()
    获取此作用域中的直接子作用域的数量
VarQuerier varquerier(int index=0)
    获取指定位置的变量的查询器
ScoQuerier scoquerier(int index=0)
    获取指定位置的作用域的查询器
```

### toCppValue函数模板

```c++
template<typename Tp>
Tp toCppValue(Value val, ValueType type)
	按照给定的ValueType将Value转换为C++ Tp类型的值，需要确保Tp、ValueType与Value三者兼容。如果Tp是不支持的类型，那么此
	函数模板将返回Tp的零值
```



## 4.2.命令

### 跳转到指定作用域

通过关键字`enter`可以进入到**绝对路径**对应的作用域中，例如对于下方的两个csc文件：

```
;a.csc
custom::
	a::
	::a
::custom

;b.csc
enter "/custom/a"
b::

::b
```

其配置内容等同于：

```
custom::
	a::
		b::
		::b
	::a
::custom
```

此功能可以便于用户将csc文件内容拆分到多个`.csc`文件中，并通过goto命令配合`CscHandler::handle`函数实现分步解析，从而将这些文件内容合并到一个CscHandler对象中。



## 4.3.辅助功能

libcsc通过action模块提供了在Command对象之外操作Context的能力，该模块可用于实现那些仅依靠Command对象无法实现的功能，下方是使用ActionMngr模块为libcsc增加的扩展功能的列举：

### 打印命令信息

**基本信息**

* 引入版本：v0.6.9
* 关键字：`action`
* 作用域：Global(全局有效)
* 使用方式：`action "detail"`
* 作用：打印后续所有命令的信息，包括命令类型、操作数、执行时的作用域ID

**使用方式**

在csc文件内插入

```
action "detail"
custom::
	name = "tom"
::custom
```

在解析阶段可以看到终端中的如下输出

```
Command type: 1; Operands: custom, ::; Scope id: 1
Command type: 3; Operands: name, =, tom; Scope id: 2
Command type: 2; Operands: ::, custom; Scope id: 2
```



# 5.项目结构

## 5.1.目录结构

* include：存放libcsc中使用到的头文件
* doc: 存放libcsc文档使用到的相关资源
* src：存放libcsc的源码文件
* README.md：项目的介绍以及使用方式
* Releasenotes.md：项目的发布信息、版本信息、特性



## 5.2.详细说明

**整体架构图**

![libcsc_structure](doc/img/libcsc_structure.png)



# 6.附录

## 支持类型

getValue和getArray函数族的模板参数Tp支持下表中的C++类型，表的右侧内容是C++类型对应的ValueType类型：

| C++类型 | ValueType类型      | 备注                                  |
| ------- | ------------------ | ------------------------------------- |
| bool    | ValueType::Bool    |                                       |
| int     | ValueType::Integer |                                       |
| long    | ValueType::Integer |                                       |
| double  | ValueType::Double  |                                       |
| String  | ValueType::String  | 在当前版本中，String等同于std::string |



## 关键字

| 关键字 | 作用                   |
| ------ | ---------------------- |
| true   | 变量赋值时作为布尔值   |
| false  | 变量赋值时作为布尔值   |
| action | 执行某个动作           |
| void   | 作为变量赋值时的占位符 |
| enter  | 进入到指定路径的作用域 |



## 作用域类型

| 作用域类型           | 功能                                                         |
| -------------------- | ------------------------------------------------------------ |
| ScopeType::MapScope  | 以std::map作为底层容器，查询效率更高，生成的字符串中变量与作用域的排列顺序会混杂 |
| ScopeType::ListScope | 以std::list作为底层容器，查询效率较低，生成的字符串会尽力维持变量与作用域的原本顺序 |

