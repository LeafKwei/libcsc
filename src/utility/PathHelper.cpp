#include "cassert"
#include "csc/utility/PathHelper.hpp"
CSC_BEGIN

PathHelper::PathHelper(const String &path){
    classify(path);
}

bool PathHelper::valid() const noexcept{
    return valid_;
}

bool PathHelper::isAbsolute() const noexcept{
    return absolute_;
}

bool PathHelper::isRoot() const noexcept{
    return absolute_ && valid_ && items_.size() == 0;
}

Size_t PathHelper::size() const noexcept{
    return items_.size();
}

String PathHelper::buildPath(int endidx) const{
    String path = (absolute_) ? "/" : "";   //根据原路径是否是绝对路径来决定是否添加根路径

    for(int i = 0; i < endidx; i++){
        path.append(items_.at(i));
        path.push_back('/');                          //最后一次循环会多出一个分隔符，需要在返回前删除
    }

    if(endidx > 0) path.pop_back();          //删除末尾多余的分隔符，检查endix是为了确保仅存在/的时候不会将其误删
    return path;
}

const String& PathHelper::item(int index) const{
    return items_.at(index);
}

const String& PathHelper::lastItem() const{
    assert(items_.size() > 0);
    return items_.at(items_.size() - 1);
}

void PathHelper::classify(const String &path){
    if(path.find('/') == 0){
        absolute_ = true;
        valid_ = splitPath(path, 1);        //index设置为1是为了跳过绝对路径的'/'
    }
    else{
        absolute_ = false;
        valid_ = splitPath(path, 0);
    }
}

bool PathHelper::splitPath(const String &path, int index){
    Size_t idx = index;

    if(path == "/"){                         //对仅存在根路径的情况做特殊处理
        return true;
    }

    while(idx < path.size()){
        auto nidx = path.find('/', idx);
        if(nidx == path.npos){          //如果没有下一个分隔符'/'并且没有到达字符串末尾，则说明字符串剩余内容是一个item
            items_.push_back(path.substr(idx));
            break;
        }

        /* 保存两个分隔符间的item，然后更新idx到下一个分隔符后的字符位置 */
        items_.push_back(path.substr(idx, (nidx - idx)));
        idx = nidx + 1;
    }

    return items_.size() > 0;
}

CSC_END