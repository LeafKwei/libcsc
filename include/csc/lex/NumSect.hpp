#ifndef CSC_NUMSECT_HPP
#define CSC_NUMSECT_HPP

#include <cstdint>
#include "csc/alias.hpp"
CSC_BEGIN

class NumSect{
public:
    using Num = uint64_t;

public:
    inline                    NumSect(Num left, Num right) noexcept;
    inline bool            contain(Num num) const noexcept;                                 //判断指定Num是否处于当前返回
    inline bool            intersect(const NumSect &other) const noexcept;           //两个范围是否存在交集
    inline bool            lessThan(const NumSect &other) const noexcept;          //当前范围内的所有数字是否都小于other内的最小数字
    inline NumSect    merge(const NumSect &other) const noexcept;              //取两个范围的并集
    inline Num           left() const noexcept;                                                        //获取左边界
    inline Num           right() const noexcept;                                                     //获取右边界
    inline void            setNum(Num left, Num right);                                         //设置边界

private:
    Num left_;
    Num right_;
};

inline NumSect::NumSect(Num left, Num right) noexcept : left_(left), right_(right){}

inline bool NumSect::contain(Num num) const noexcept{
    return (num >= left_ && num <= right_);
}

inline bool NumSect::intersect(const NumSect &other) const noexcept{
    return (contain(other.right_)) || (other.contain(right_));
}

inline bool NumSect::lessThan(const NumSect &other) const noexcept{
    return right_ < other.left_;
}

inline NumSect NumSect::merge(const NumSect &other) const noexcept{
    auto min = (left_ < other.left_) ? left_ : other.left_;
    auto max = (right_ > other.right_) ? right_ : other.right_;
    return NumSect(min, max);
}

inline NumSect::Num NumSect::left() const noexcept{
    return left_;
}

inline NumSect::Num NumSect::right() const noexcept{
    return right_;
}

inline void NumSect::setNum(Num left, Num right){
    left_ = left;
    right_ = right;
}

CSC_END
#endif