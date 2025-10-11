#ifndef CSC_PATHHELPER_HPP
#define CSC_PATHHELPER_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

class PathHelper{
public:
    using PathItemList = std::vector<String>;

public:
    bool      isAbsolute() const noexcept;      //检查该路径是否是绝对路径
    crString item(int index) const noexcept;  //获取给定位置的item
    crString lastItem() const noexcept;          //获取最末尾的item
    Size_t    count() const noexcept;              //获取path分解得到的item数量

private:
    bool              m_absolute;
    PathItemList m_items;
};

CSC_END
#endif