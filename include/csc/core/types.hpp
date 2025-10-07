#ifndef CSC_CORE_TYPES_HPP
#define CSC_CORE_TYPES_HPP

#include <vector>
#include <memory>
#include <map>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

/**
 * 下方的别名被用于CscHandler::getValue系列函数，如果Context中保存的variable具有多个值，可以通过为getValue指定下方的类型来获取一个vector。
 * csc目前仅支持bool、int/long(底层都使用long，但是用户可以选择按int转换)、double、std::string四种类型的数据，在context/types.hpp中定义了
 * 枚举ValueType，用于在Context中标记std::any中存储的是何种类型的数据
 */
using array_bool = std::vector<bool>;
using array_int    = std::vector<int>;
using array_long = std::vector<long>;
using array_double = std::vector<double>;
using array_string = std::vector<String>;

CSC_END
#endif