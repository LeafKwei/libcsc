#include "csc/utility/PathHelper.hpp"
#include <iostream>
CSC_BEGIN

PathHelper::PathHelper() : absolute_(false){

}

PathHelper::PathHelper(const String &path){
    decompose(path);
}

bool PathHelper::rootonly() const noexcept{
    return absolute() && elements_.empty();
}

bool PathHelper::absolute() const noexcept{
    return absolute_;
}

bool PathHelper::valid() const noexcept{
    return (elements_.size() > 0) || rootonly();
}

bool PathHelper::complex() const noexcept{
    return (elements_.size() > 1) || (absolute_ && !elements_.empty());  //路径元素大于2(例如a/b)或者是根路径变量(例如/a)
}

void PathHelper::decompose(const String &path){
    absolute_ = false;
    if(path.size() == 0){
            return;
    }

    /* 按绝对路径处理 */
    if(path.at(0) == '/'){
        absolute_ = true;
        do_decompose(path, 1);
        return;
    }

    /* 按相对路径处理 */
    do_decompose(path, 0);
}

String PathHelper::compose(int endidx) const{
    String path = (absolute_) ? "/" : ""; 
    auto safeidx = ((static_cast<Size_t>(endidx)) > elements_.size()) ? elements_.size() : endidx;

    for(Size_t i = 0; i < safeidx; i++){
        path.append(elements_.at(i));
        path.push_back('/');
    }

    if(safeidx > 0) path.pop_back();     //删除末尾多余的/
    return path;
}

String PathHelper::element(int index) const{
    return elements_.at(index);
}

String PathHelper::dirname() const{
    return compose(elements_.size() - 1);
}

String PathHelper::basename() const{
    return (elements_.empty()) ? "" : elements_.at(elements_.size() - 1);
}

Size_t PathHelper::size() const noexcept{
    return elements_.size();
}

void PathHelper::do_decompose(const String &path, int index){
    Size_t idx = index;

    while(idx < path.size()){
        auto nidx = path.find('/', idx);
        if(nidx == path.npos){          //如果没有下一个分隔符'/'并且没有到达字符串末尾，则说明字符串剩余内容是一个item
            elements_.push_back(path.substr(idx));
            break;
        }

        /* 如果连续出现//，则视为无效路径并停止解析 */
        if(nidx == idx){
            reset();
            return;
        }

        /* 保存两个分隔符间的element，然后更新idx到下一个分隔符后的字符位置 */
        elements_.push_back(path.substr(idx, (nidx - idx)));
        idx = nidx + 1;
    }
}

void PathHelper::reset(){
    absolute_ = false;
    elements_.clear();
}

CSC_END