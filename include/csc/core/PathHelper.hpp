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
    PathHelper(crString path);

    bool      valid() const noexcept;           //检查路径是否是有效格式
    bool      isAbsolute() const noexcept; //检查该路径是否是绝对路径
    bool      isRoot() const noexcept;       //是否是根路径
    Size_t    size() const noexcept;           //获取path分解得到的item数量
    String    buildPath(int endidx) const; //从index 0开始到index endidx(不包括)结束，将其中的item合并为一个路径，当isAbsolute为true时，路径之前会添加'/'
    crString item(int index) const;           //获取给定位置的item
    crString lastItem() const;                   //获取最末尾的item

private:
    bool              m_valid;
    bool              m_absolute;
    PathItemList m_items;

    void classify(crString path);
    bool splitPath(crString path, int index);
};

CSC_END
#endif