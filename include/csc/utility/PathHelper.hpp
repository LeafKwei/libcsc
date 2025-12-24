#ifndef CSC_PATHHELPER_HPP
#define CSC_PATHHELPER_HPP

#include <vector>
#include "csc/alias.hpp"
CSC_BEGIN

class PathHelper{
public:
    using PathElementList = std::vector<String>;

public:
    PathHelper();
    PathHelper(const String &path);

    bool rootonly() const noexcept;           /* 是否仅是一个根路径，即/ */
    bool absolute() const noexcept;          /* 路径是否为绝对路径 */
    bool valid() const noexcept;                 /* 路径是否有效 */
    bool complex() const noexcept;          /* 路径是否同时具有dirname和basename两部分 */
    void decompose(const String &path); /* 将路径以/为界限分解为单个组成部分*/
    String compose(int endidx) const;       /* 将endix之前的所有路径元素组合为一个路径  */
    String element(int idx) const;              /* 获取给定位置的路径元素 */
    String dirname() const;                       /* 如果路径为/a/b或a/b，那么此函数用于获取/a部分和a部分 */ 
    String basename() const;                    /* 如果路径为/a/b或a/b或b，那么此函数用于获取b部分 */
    Size_t size() const noexcept;              /* 获取路径元素数量，不包含根路径 */

private:
    PathElementList elements_;
    bool                    absolute_;

    void reset();
    void do_decompose(const String &path, int idx);
};

CSC_END
#endif